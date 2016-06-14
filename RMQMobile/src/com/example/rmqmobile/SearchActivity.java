package com.example.rmqmobile;

import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.DatePicker;
import android.widget.TextView;
import android.widget.Toast;

public class SearchActivity extends Activity {
	private DatabaseHandler db;
    TextView showCall;
    TextView showSMS;
    TextView showTotalCall;
    TextView showTotalSMS;
	DatePicker datePicker;
	
	

	@Override
    public void onCreate(Bundle savedInstanceState) 
    {

		super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);
        showCall = (TextView)findViewById(R.id.show_call);
        showSMS =(TextView)findViewById(R.id.show_sms);
        showTotalCall = (TextView)findViewById(R.id.show_total_call);
        showTotalSMS =(TextView)findViewById(R.id.show_total_sms);
        datePicker= (DatePicker)findViewById(R.id.datePicker1);
        db = new DatabaseHandler(this);
        
        Contact contact=db.getContact(Contact.TIME, Contact.TOTAL);
        if (contact!=null)
        {
            showTotalCall.setText(String.valueOf(contact.call));
            showTotalSMS.setText(String.valueOf(contact.sms));       	
        }else
        {
        	 showTotalCall.setText(String.valueOf(0));
             showTotalSMS.setText(String.valueOf(0));       	
        }
    }
    
    public void startdb(View view)
    {
        // Inserting Contacts
        Log.d("Insert: ", "Inserting ..");
        
        db.addContact(new Contact("am",23,3));//));
        db.addContact(new Contact("pm", 1,8));
        db.addContact(new Contact("Tommy", 9,6));
        db.addContact(new Contact("out", 3,5));    	
    	
        Log.d("find:","am");
        Contact c=db.getContact("time", "sad");
        if (c==null)
        		return;
        Log.d("show",String.valueOf(c.call));
    }
    
    public void findindb(View view)
    {   	               
        Log.d("Reading: ", "Reading all contacts..");
        
        int year=datePicker.getYear();
        int month=datePicker.getMonth()+1;
        int date=datePicker.getDayOfMonth();
        String s=TimeStamp.getTime(year, month, date);
        
        Contact contact=db.getContact(Contact.TIME, s);
        if (contact==null)
        {
        	Toast.makeText(getApplicationContext(),"no data", Toast.LENGTH_SHORT).show();
            showCall.setText(String.valueOf(0));
            showSMS.setText(String.valueOf(0));
        	return;    
        }
        showCall.setText(String.valueOf(contact.call));
        showSMS.setText(String.valueOf(contact.sms));
        
        
        contact=db.getContact(Contact.TIME, Contact.TOTAL);
        if (contact!=null)
        {
            showTotalCall.setText(String.valueOf(contact.call));
            showTotalSMS.setText(String.valueOf(contact.sms));       	
        }else
        {
        	 showTotalCall.setText(String.valueOf(0));
             showTotalSMS.setText(String.valueOf(0));       	
        }
        
    }
    
    public void listall()
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
    public void clear(View view)
    {
    	db.clearContact();
    }
    
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        getMenuInflater().inflate(R.menu.activity_search, menu);
        return true;
    }   
    
    

}
