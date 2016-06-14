package com.example.rmqmobile;


public class Contact {
 
    //private variables
    public int id;
    public String time;
    public int  call;
    public int sms;
    public final static String ID="id";
    public final static String TIME="time";
    public final static String CALL="call";
    public final static String SMS="sms";
    public final static String TOTAL="total";
    public final static String TABLE="contactcount";
    // Empty constructor
    public Contact(){
 
    }
    // constructor
    public Contact(int id, String time, int call,int sms){
        this.id = id;
        this.time = time;
        this.call = call;
        this.sms=sms;
    }
 
    // constructor
    public Contact(String time, int call,int sms)
    {
        this.time = time;
        this.call = call;
        this.sms=sms;
    }


    
    
}