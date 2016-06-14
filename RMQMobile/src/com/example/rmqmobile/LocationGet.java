package com.example.rmqmobile;

import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;

public class LocationGet implements LocationListener
{	
	
	LocationManager locMan;
	Location location;
	long waitTime=1000;
	public void setTimer(int freq)
	{
		waitTime=freq*60*1000;
	}
	
	
	public void start()
	{
		locMan.requestLocationUpdates(LocationManager.NETWORK_PROVIDER,waitTime ,10 ,this);          
        //locMan.requestLocationUpdates(LocationManager.GPS_PROVIDER,waitTime,10 ,this);  
        //locMan.removeGpsStatusListener(GpsStatus.Listener);
		//location = locMan.getLastKnownLocation(LocationManager.GPS_PROVIDER);  
        //if (location== null)  
        location = locMan.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);           
	}
	public LocationGet(LocationManager locMan)
	{
		this.locMan=locMan;
		start();
	}
	
	public void onLocationChanged(Location location) {
		// TODO Auto-generated method stub
		this.location=location;
		
	}

	
	public void onProviderDisabled(String provider) {
		// TODO Auto-generated method stub
		
	}

	
	public void onProviderEnabled(String provider) {
		// TODO Auto-generated method stub
		
	}

	
	public void onStatusChanged(String provider, int status, Bundle extras) {
		// TODO Auto-generated method stub
		
	}
	
	public void cancel()
	{
		locMan.removeUpdates(this);
	}
	
	
}
