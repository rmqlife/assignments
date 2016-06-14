package com.example.rmqmobile;

import java.io.File;
import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Display;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

public class MainActivity extends Activity {
	public final static String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";
	private EditText editText=null;
	public ImageView imv;
	private DatabaseHandler db;
	public String imageFilePath;
	public final static String EXTRA_COLLECT_SEND = "com.example.rmqmobile.MainActivity.COLLECT_SEND";
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
    	//stopService(new Intent(this, RMQMobileService.class));
    	super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //default set service 
        imageFilePath = Environment.getExternalStorageDirectory().getAbsolutePath()+"/RMQMobile/simbol.jpg";
        db = new DatabaseHandler(this);
        editText= (EditText) findViewById(R.id.edit_message);
        showHead();
    }
    

    private void finishMain()
    {
    	
    	RMQApplication app=(RMQApplication)this.getApplication();
    	if (app.serviceRun)
    		stopService(new Intent(this, RMQMobileService.class));
    	
    	this.finish();
    }
    public void onDestroy()
    {
    	System.exit(0);
    }
    
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
    
    
    //send button
    public void sendMessage(View view)
    {
    	Intent intent = new Intent(this, DisplayMessageActivity.class);    	    	
    	String message = editText.getText().toString();
    	intent.putExtra(EXTRA_MESSAGE, message);
    	startActivity(intent);
    }
    
    public void setNetwork(View view)
    {
    	Intent intent=new Intent(this,NetworkActivity.class);
    	startActivity(intent);
    }
    public void setNetwork()
    {
    	Intent intent=new Intent(this,NetworkActivity.class);
    	startActivity(intent);
    }
    
    
    public void getSensor(View view)
    {
    	Intent intent=new Intent(this,SensorActivity.class);
    	startActivity(intent);
    }
    public void getSensor()
    {
    	Intent intent=new Intent(this,SensorActivity.class);
    	startActivity(intent);
    }
    
    
    public void setPhone()
    {    		
    	Intent intent=new Intent(this,SearchActivity.class);
    	startActivity(intent);
    }
    
    public void setSearch()
    {
    	Intent intent=new Intent(this,SensorSearchActivity.class);
    	startActivity(intent);
    }
	
    public void collectSend()
    {
    	//String s="collect";
        Intent intent=new Intent(EXTRA_COLLECT_SEND);
	    //intent.putExtra(IP_ADDRESS, s);
	    sendBroadcast(intent);
    }
	@Override
	public boolean onOptionsItemSelected(MenuItem item) 
	{
		switch(item.getItemId())
		{
		case R.id.network_setting:setNetwork();break;
		case R.id.menu_phone:setPhone();break;
		case R.id.menu_sensor:getSensor();break;
		case R.id.menu_search:setSearch();break;
		case R.id.item_exit:exitAlert();break;
		case R.id.item_collect_send:collectSend();break;
		}
		return false;
	}
	
	private void exitAlert()
	{
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setMessage("Are you sure to exit?")
		       .setCancelable(false)
		       .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
		           public void onClick(DialogInterface dialog, int id) 
		           {
		               //MainActivity.this.finish();		               
		        	   finishMain();
		           }
		       })
		       .setNegativeButton("No", new DialogInterface.OnClickListener() {
		           public void onClick(DialogInterface dialog, int id) {
		                dialog.cancel();
		           }
		       });
		AlertDialog alert = builder.create();
		alert.show();
	}
	
	
    public void findall()
    {
        List<Contact> contacts = db.getAllContacts();      
        
        String sp=" ";
        for (Contact cn : contacts) 
        {
            String log = "Id: "+cn.id
            		+sp+Contact.TIME+sp+cn.time
            		+sp+Contact.CALL+sp+cn.call
            		+sp+Contact.SMS+sp+cn.sms;
            // Writing Contacts to log
            Log.d("Name: ", log);
        }
        List<DataPack> sensor =db.getAllSensors();
        Log.d("sensor length",String.valueOf(sensor.size()));
        for (DataPack c:sensor)
        {
        	String log=c.objectToString();
        	Log.d("sensor",log);
        }
    	
    }
   
    
    public void loadPicture(View view)
    {
        Intent intent=new Intent(NetworkActivity.EXTRA_DOWNLOAD_PIC);	    
	    sendBroadcast(intent);
    }
    
    
    public void takePhoto(View view)
    {
	    Intent intent = new Intent(this, CameraActivity.class);    	    	

		startActivity(intent);
    }
    
    public void updatePicture(View view)
    {
        //Intent intent=new Intent(NetworkActivity.EXTRA_UPLOAD_PIC);	    
	    //sendBroadcast(intent);
    	showHead();
    }
    
    public void showHead()
    {
 	   File file=new File(imageFilePath);
 	   if (!file.exists())
 	   {
 			   Toast.makeText(getApplicationContext(), "No head picture!", Toast.LENGTH_LONG).show();
 			   return;
 	   }
       imv = (ImageView) findViewById(R.id.imageView1);
 	   Display currentDisplay = getWindowManager().getDefaultDisplay();
 	   int dw = currentDisplay.getWidth();
 	   int dh = currentDisplay.getHeight();
 	   // Load up the image's dimensions not the image itself
 	   
 	   BitmapFactory.Options bmpFactoryOptions = new BitmapFactory.Options();
 	   bmpFactoryOptions.inJustDecodeBounds = true;
 	   
 	   
 	   Bitmap bmp = BitmapFactory.decodeFile(imageFilePath, bmpFactoryOptions);
 	   int heightRatio = (int)Math.ceil(bmpFactoryOptions.outHeight/(float)dh);
 	   int widthRatio = (int)Math.ceil(bmpFactoryOptions.outWidth/(float)dw);
 	   Log.v("HEIGHTRATIO",""+heightRatio);
 	   Log.v("WIDTHRATIO",""+widthRatio);
 	   // If both of the ratios are greater than 1,
 	   // one of the sides of the image is greater than the screen
 	   if (heightRatio > 1 && widthRatio > 1)
 	   {
 		    if (heightRatio > widthRatio)
 		    {
 		     // Height ratio is larger, scale according to it
 		     bmpFactoryOptions.inSampleSize = heightRatio;
 		    }
 		    else
 		    {
 		     // Width ratio is larger, scale according to it
 		     bmpFactoryOptions.inSampleSize = widthRatio;
 		    }
 	   }
 	   // Decode it for real
 	   bmpFactoryOptions.inJustDecodeBounds = false;
 	   bmp = BitmapFactory.decodeFile(imageFilePath, bmpFactoryOptions);
 	   
 	   // Display it
 	   imv.setImageBitmap(bmp);
    	
    	
    }
    
}
