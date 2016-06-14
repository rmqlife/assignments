package com.example.rmqmobile;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class DisplayMessageActivity extends Activity {
	String ret="\n\r";
	String spt=" :";
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Get the message from the intent
        Intent intent = getIntent();
        String message = intent.getStringExtra(MainActivity.EXTRA_MESSAGE);
        String show="null";
        if (message.equals("loc"))
        	show=getLocation();
        if (message.equals("wifi"))
        	show=getWifi();
        // Create the text view
        TextView textView = new TextView(this);
        textView.setTextSize(20);
        textView.setText("Command"+spt+message+ret+show);
        				

        // Set the text view as the activity layout
        setContentView(textView);
        }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        getMenuInflater().inflate(R.menu.activity_display_message, menu);
        return true;
    }
    
    
    public String getLocation()
    {
       LocationListener mLocationListener01 =  new  LocationListener(){
               
            public   void  onLocationChanged(Location location) {}       
               
            public   void  onProviderDisabled(String provider) {}        
               
            public   void  onProviderEnabled(String provider) {}       
               
            public   void  onStatusChanged(String provider,  int  status, Bundle extras) {}  
        	};        
         LocationManager locMan = (LocationManager) getSystemService(Context.LOCATION_SERVICE);  
         locMan.requestLocationUpdates(LocationManager.NETWORK_PROVIDER,1000 ,10 ,mLocationListener01);          
         locMan.requestLocationUpdates(LocationManager.GPS_PROVIDER,1000,10 ,mLocationListener01);  
         Location location = locMan.getLastKnownLocation(LocationManager.GPS_PROVIDER);  
         if (location== null )  
               location = locMan.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);  
          String result="Latitude"+spt+location.getLatitude()+ret
        		 +"Longitude"+spt+location.getLongitude()+ret;
          return result;            	
    }
    
    
    public String  getWifi()
    {
    	 
    	WifiManager wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);  
    	WifiInfo info = wifi.getConnectionInfo();  
    	String maxText = info.getMacAddress();  
    	String ipText = String.valueOf(info.getIpAddress());  
    	String status = "";  
    	if (wifi.getWifiState() == WifiManager.WIFI_STATE_ENABLED)  
    	{  
    	status = "WIFI_STATE_ENABLED";  
    	}  
    	String ssid = info.getSSID();  
    	int networkID = info.getNetworkId();  
    	int speed = info.getLinkSpeed();  
    	int rssi= info.getRssi();
    	String result= "mac：" + maxText + "\n\r"  
    	+ "ip：" + ipText + "\n\r"  
    	+ "wifi status :" + status + "\n\r"  
    	+ "ssid :" + ssid + "\n\r"  
    	+ "net work id :" + networkID + "\n\r"  
    	+ "connection speed:" + speed + "\n\r"
    	+ "rssi : "+ rssi
    	;  	
    	return result;
    }
     
}
