package com.example.rmqmobile;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;

public class RMQSensor implements SensorEventListener {
	 private  SensorManager sensorManager;
	 private LocationManager locMan;
	 public  float magValue,lightValue,gravValue,aXValue,aYValue,aZValue;
	 private int []sensorType=new int[]{Sensor.TYPE_GRAVITY,Sensor.TYPE_LIGHT,Sensor.TYPE_MAGNETIC_FIELD,Sensor.TYPE_ACCELEROMETER};

	 public RMQSensor(SensorManager sm,LocationManager lm)
	 {
		 sensorManager=sm;		 
		 start();
		 locMan=lm;
		 getLocation();
	 }
	 
	 
	 public Location getLocation()
	 {
	       LocationListener mLocationListener01 =  new  LocationListener()
	       {
	               
	            public   void  onLocationChanged(Location location) {}       
	               
	            public   void  onProviderDisabled(String provider) {}        
	               
	            public   void  onProviderEnabled(String provider) {}       
	               
	            public   void  onStatusChanged(String provider,  int  status, Bundle extras) {}  
	        };        
	         locMan.requestLocationUpdates(LocationManager.NETWORK_PROVIDER,1000 ,10 ,mLocationListener01);          
	         locMan.requestLocationUpdates(LocationManager.GPS_PROVIDER,1000,10 ,mLocationListener01);  
	         Location location = locMan.getLastKnownLocation(LocationManager.GPS_PROVIDER);  
	         if (location== null )  
	               location = locMan.getLastKnownLocation(LocationManager.NETWORK_PROVIDER); 
	         return location;
	 }
	 
	 
    public void start()
    {
		
		// add listener. The listener will be HelloAndroid (this) class
		for (int i=0;i<sensorType.length;i++)
			sensorManager.registerListener(this,sensorManager.getDefaultSensor(sensorType[i]),SensorManager.SENSOR_DELAY_NORMAL); 
    }
    

	
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub
		
	}

	
	public void onSensorChanged(SensorEvent event) {
		switch (event.sensor.getType())
		{
		case Sensor.TYPE_GRAVITY:showGrav(event);break;
		case Sensor.TYPE_ACCELEROMETER:showAccelerate(event);break;
		
		case Sensor.TYPE_LIGHT:showLight(event);break;
		case Sensor.TYPE_MAGNETIC_FIELD:showMag(event);break;
		}
		
		//switchSensor();
		
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
	
	public void cancel()
	{
		sensorManager.unregisterListener(this);
	}
	
	public void onDestroy()
	{
		cancel();
	}
	
}
