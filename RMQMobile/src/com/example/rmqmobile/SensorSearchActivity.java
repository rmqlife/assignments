package com.example.rmqmobile;

import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.GestureDetector;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ArrayAdapter;
import android.widget.DatePicker;
import android.widget.ListView;
import android.widget.Toast;
import android.widget.ViewFlipper;
public class SensorSearchActivity extends Activity {
	
	ListView listView;
	ViewFlipper flipper;
	GestureDetector mGestureDetector;
	private DatabaseHandler db;
	int order=0;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sensor_search);
        //sensorlist = (ListView)findViewById(R.id.listView1);
        db = new DatabaseHandler(this);
        setupViewList();           
    	} 
       
    
    private void setupViewList()
    {
    	listView = new ListView(this);
    	//listView = (ListView)findViewById(R.id.listView1);
    	if (db.getSensorsCount()>0)
    		listView.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_expandable_list_item_1,getData()));
    	else
    		Toast.makeText(getApplicationContext(), "No data in database", Toast.LENGTH_LONG).show();
    	setContentView(listView);
    }
    


    private List<String> getData()
    {            

        List<DataPack> sensor =db.getAllSensors();
        Log.d("sensor length",String.valueOf(sensor.size()));
        /*for (DataPack c:sensor)
        {
        	String log=c.objectToString();
        	Log.d("sensor",log);
        }*/
    	DataPack s1=sensor.get(order);
    	return s1.getList();
    }
    
    
    private void nextData()
    {   	
    	if (order+1>=db.getSensorsCount())
    	{
    		Toast.makeText(getApplicationContext(), "request out of range", Toast.LENGTH_SHORT).show();
    		return;
    	}
    	order++;
    	setupViewList();
    }
    
    private void prevData()
    {
    	if (order-1<0)
    	{
    		Toast.makeText(getApplicationContext(), "request out of range", Toast.LENGTH_SHORT).show();
    		return;
    	}
    	order--;
    	setupViewList();
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        getMenuInflater().inflate(R.menu.activity_search_sensor, menu);
        return true;
    }
    
	@Override
	public boolean onOptionsItemSelected(MenuItem item) 
	{
		switch(item.getItemId())
		{
		case R.id.item_next:nextData();break;
		case R.id.item_prev:prevData();break;
		case R.id.item_upload_all:uploadAllData();break;
		case R.id.item_download:makeDialog();break;
		case R.id.item_clear:clear();break;
		}
		return false;
	}

    public void uploadAllData()
    {
        Intent intent=new Intent(NetworkActivity.EXTRA_UPLOAD_ALL_DATA);	    
	    sendBroadcast(intent);
    }
    
    public void downloadData(String date)
    {
    	Intent intent=new Intent(NetworkActivity.EXTRA_DOWNLOAD_DATA);
    	//TODO
	    intent.putExtra(NetworkActivity.EXTRA_DOWNLOAD_IN, date);
    	sendBroadcast(intent);
    }
    
    	protected void makeDialog() 
    	{
    		  AlertDialog.Builder builder = new Builder(this);
    		  //builder.setMessage("确认退出吗？");
    		  final DatePicker dp=new DatePicker(this);
    		  builder.setView(dp);
    		  builder.setTitle("Input Date");
    		  builder.setPositiveButton("sure", new OnClickListener() 
    		  {

    		   public void onClick(DialogInterface dialog, int which) 
    		   {
    			downloadData(dp.getYear()+"-"+(dp.getMonth()+1)+"-"+dp.getDayOfMonth());
    		    dialog.dismiss();
    		   }
    		  });

    		  builder.setNegativeButton("cancel", new OnClickListener() 
    		  {

    		   public void onClick(DialogInterface dialog, int which) {
    		    dialog.dismiss();
    		   }
    		  });

    		  builder.create().show();
    	}
    	public void clear()
    	{
    		db.clearSensor();
    	}
  }
    
