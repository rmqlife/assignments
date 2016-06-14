package com.example.rmqmobile;

import android.app.Application;
import android.content.Intent;

public class RMQApplication extends Application
{
public boolean serviceRun=true;

public String userName,userPassword,ipAddress;
public int getfrequency;
//private boolean ServiceOn=false;
public void onCreate()
{
	if (serviceRun)
        startService(new Intent(this, RMQMobileService.class));
    else
    	stopService(new Intent(this, RMQMobileService.class));
}



}
