package com.example.rmqmobile;

import java.util.Calendar;

public class TimeStamp {
	
	final public static String sp="/";
	
	public static String getTimeStamp()
	{
		Calendar c=Calendar.getInstance();
		//Sensor sensor=Sensormanager.ge
		int year=c.get(Calendar.YEAR);
		int month=c.get(Calendar.MONTH)+1;
		int date=c.get(Calendar.DATE);
					
		int hour=c.get(Calendar.HOUR);
		if (c.get(Calendar.AM_PM)==Calendar.PM)
			hour+=12;
		int min=c.get(Calendar.MINUTE);
		int sec=c.get(Calendar.SECOND);
		
		String result=year+"-"+month+"-"+date+" "
				+hour+":"+min+":"+sec;
		return result;
	}
	public static String getTime(int year,int month,int date)
	{
		String s=year+sp+month+sp+date;
		return s;
	}
	
	public static String getDate()
	{
		Calendar c=Calendar.getInstance();
		int year=c.get(Calendar.YEAR);
		int month=c.get(Calendar.MONTH)+1;
		int date=c.get(Calendar.DATE);
		return getTime(year,month,date);
	}
	
	
}
