package com.example.rmqmobile;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class SensorActivity extends Activity implements SensorEventListener{
	  private ListView listView;
	  private  SensorManager sensorManager;
	  float magValue,lightValue,gravValue,aXValue,aYValue,aZValue;
	  private int []sensorType=new int[]{Sensor.TYPE_GRAVITY,Sensor.TYPE_LIGHT,Sensor.TYPE_MAGNETIC_FIELD,Sensor.TYPE_ACCELEROMETER};
	  //private static Timer timer;
	  //private List<String> data = new ArrayList<String>();
	    @Override
	    public void onCreate(Bundle savedInstanceState){
	        super.onCreate(savedInstanceState);

	        //Toast.makeText(getApplicationContext(), String.valueOf(gravValue), Toast.LENGTH_SHORT).show();	    	
	        //timer=new Timer();
	        
	        setupSensor();
	        //timer.scheduleAtFixedRate(new mainTask(), 0, 3000);
	    }
    
	    private void setupViewList()
	    {
	    	listView = new ListView(this);
	    	//listView = (ListView)findViewById(R.id.listView1);
	        listView.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_expandable_list_item_1,getData()));
	        setContentView(listView);

	    }
	    
	    public void onDestroy()
	    {
	    	super.onDestroy();
	        sensorManager.unregisterListener(this);
	    }
	    
	    
	    
	    private void setupSensor()
	    {
			sensorManager=(SensorManager)getSystemService(SENSOR_SERVICE);
			// add listener. The listener will be HelloAndroid (this) class
			for (int i=0;i<sensorType.length;i++)
				sensorManager.registerListener(this,sensorManager.getDefaultSensor(sensorType[i]),SensorManager.SENSOR_DELAY_NORMAL); 
	    }
	    
	    
	    private List<String> getData(){
	    	//ArrayList<HashMap<String, Object>> listItem = new ArrayList<HashMap<String, Object>>();    
	        List<String> data = new ArrayList<String>();
	        //Map<String,String> map1=new HashMap<String,String>();
	        //map1.put("Gravity", t1);	        
	        String t;
	        t="Grav:"+gravValue;
	        data.add(t);
	        t="Light:"+lightValue;
	        data.add(t);
	        t="Magf:"+magValue;
	        data.add(t);
	        t="Acl x:"+aXValue;
	        data.add(t);
	        t="Acl y:"+aYValue;
	        data.add(t);
	        t="Acl z:"+aZValue;
	        data.add(t);
	        t=TimeStamp.getTimeStamp();
	        data.add("Time:"+t);			
	        return data;
	    }
	    
	    
		
		public void onAccuracyChanged(Sensor sensor, int accuracy) {
			// TODO Auto-generated method stub
		}
		
		
		
		public void onSensorChanged(SensorEvent event) 
		{
			// TODO Auto-generated method stub
			switch (event.sensor.getType())
			{
			case Sensor.TYPE_GRAVITY:showGrav(event);break;
			case Sensor.TYPE_ACCELEROMETER:showAccelerate(event);break;
			
			case Sensor.TYPE_LIGHT:showLight(event);break;
			case Sensor.TYPE_MAGNETIC_FIELD:showMag(event);break;
			}
			
			//switchSensor();
			setupViewList();
		}
		
		private void showAccelerate(SensorEvent event)
		{
			// assign directions
			 aXValue=event.values[0];
			 aYValue=event.values[1];
			 aZValue=event.values[2];					
							
		}
		private void showLight(SensorEvent event)
		{
			 lightValue=event.values[0];
			
		}
		
		private void showMag(SensorEvent event)
		{
			magValue=event.values[0];
				
		}
		private void showGrav(SensorEvent event)
		{
			gravValue=event.values[0];			
		}
		
	}