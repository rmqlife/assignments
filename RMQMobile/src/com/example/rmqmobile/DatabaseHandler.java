package com.example.rmqmobile;
 
import java.util.ArrayList;
import java.util.List;
 
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
 
public class DatabaseHandler extends SQLiteOpenHelper {
 
    // All Static variables
    // Database Version
    private static final int DATABASE_VERSION = 1;
 
    // Database Name
    private static final String DATABASE_NAME = "contactsManager";
 
    // Contacts table name WARNING:if it is changed you should run to delete the whole database!!!
    private static final String TABLE_CONTACTS = "contacts";
    private static final String TABLE_SENSOR = "sensor";
    
    
    // Contacts Table Columns names
    private static final String KEY_ID = Contact.ID;
    private static final String KEY_TIME = Contact.TIME;
    private static final String KEY_CALL = Contact.CALL;
    private static final String KEY_SMS= Contact.SMS;
    
    
    

    public DatabaseHandler(Context context) {
        
    	super(context, DATABASE_NAME, null, DATABASE_VERSION);
        //to refresh Database
    	//SQLiteDatabase db = this.getWritableDatabase();
        //context.deleteDatabase(db.getPath());
    }
 
    // Creating Tables
    
    public void onCreate(SQLiteDatabase db) {
    	
    	String data_type_float=" FLOAT,";
    	String data_type_string=" TEXT,";
        String CREATE_SENSOR_TABLE = "CREATE TABLE " + TABLE_SENSOR + "("
                + KEY_ID + " INTEGER PRIMARY KEY," + DataPack.KEY_TIMESTAMP + data_type_string
                + DataPack.KEY_MAG + data_type_float + DataPack.KEY_LIGHT+data_type_float
                + DataPack.KEY_GRAV+ data_type_float + DataPack.KEY_AX+data_type_float
                + DataPack.KEY_AY+ data_type_float + DataPack.KEY_AZ+ data_type_float
                + DataPack.KEY_LONGT+ data_type_string+ DataPack.KEY_LAT+data_type_string
                + DataPack.KEY_WIFI_SSID+ data_type_string+ DataPack.KEY_WIFI_MAC+" TEXT,"
                + DataPack.KEY_WIFI_RSSI+" INT)";
        db.execSQL(CREATE_SENSOR_TABLE);
        
        
        String CREATE_CONTACTS_TABLE = "CREATE TABLE " + TABLE_CONTACTS + "("
                + KEY_ID + " INTEGER PRIMARY KEY," + KEY_TIME + " TEXT,"
                + KEY_CALL + " INT," + KEY_SMS+" INT)";
        db.execSQL(CREATE_CONTACTS_TABLE);
    }
 
    // Upgrading database
    
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Drop older table if existed
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_CONTACTS);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_SENSOR);
        // Create tables again
        onCreate(db);
    }
 
    /**
     * All CRUD(Create, Read, Update, Delete) Operations
     */
 
    // Adding new contact
    void addContact(Contact contact) {
        SQLiteDatabase db = this.getWritableDatabase();
 
        ContentValues values = new ContentValues();
        values.put(KEY_TIME, contact.time); // Contact Name
        values.put(KEY_CALL, contact.call); // Contact Phone
        values.put(KEY_SMS, contact.sms);
        // Inserting Row
        db.insert(TABLE_CONTACTS, null, values);
        db.close(); // Closing database connection
    }
    
    void addSensor(DataPack data) {
        SQLiteDatabase db = this.getWritableDatabase();
 
        ContentValues values = new ContentValues();
        values.put(DataPack.KEY_TIMESTAMP, data.timeStamp); 
        values.put(DataPack.KEY_MAG, data.magValue);
        values.put(DataPack.KEY_LIGHT, data.lightValue);
        values.put(DataPack.KEY_GRAV, data.gravValue);
        values.put(DataPack.KEY_AX, data.aXValue);
        values.put(DataPack.KEY_AY, data.aYValue);
        values.put(DataPack.KEY_AZ, data.aZValue);
        values.put(DataPack.KEY_LONGT, data.longtitude);
        values.put(DataPack.KEY_LAT, data.lattitude);
        values.put(DataPack.KEY_WIFI_SSID, data.ssid);
        values.put(DataPack.KEY_WIFI_MAC, data.mac);
        values.put(DataPack.KEY_WIFI_RSSI, data.rssi);
        // Inserting Row
        db.insert(TABLE_SENSOR, null, values);
        db.close(); // Closing database connection
    }
    
    
    // Getting single contact
    Contact getContact(int id) 
    {
        SQLiteDatabase db = this.getReadableDatabase();
 
        Cursor cursor = db.query(TABLE_CONTACTS, new String[] { KEY_ID,
                KEY_TIME, KEY_CALL }, KEY_ID + "=?",
                new String[] { String.valueOf(id) }, null, null, null, null);
        if (cursor != null)
            cursor.moveToFirst();
 
        Contact contact = new Contact(Integer.parseInt(cursor.getString(0)),
                cursor.getString(1), Integer.parseInt(cursor.getString(2)),Integer.parseInt(cursor.getString(3)));
        // return contact
        db.close();
        return contact;
    }
    
    // Getting All Contacts
    public List<Contact> getAllContacts() {
        List<Contact> contactList = new ArrayList<Contact>();
        // Select All Query
        String selectQuery = "SELECT  * FROM " + TABLE_CONTACTS;
 
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor cursor = db.rawQuery(selectQuery, null);
 
        // looping through all rows and adding to list
        if (cursor.moveToFirst()) {
            do {
                Contact contact = new Contact();
                contact.id=Integer.parseInt(cursor.getString(0));
                contact.time=cursor.getString(1);
                contact.call=(Integer.parseInt(cursor.getString(2)));
                contact.sms=(Integer.parseInt(cursor.getString(3)));
                contactList.add(contact);
            } while (cursor.moveToNext());
        }
        db.close();
        // return contact list
        return contactList;
    }
    
    // Getting All Contacts
    public List<DataPack> getAllSensors() {
        List<DataPack> sensorList = new ArrayList<DataPack>();
        // Select All Query
        String selectQuery = "SELECT  * FROM " + TABLE_SENSOR;
 
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor cursor = db.rawQuery(selectQuery, null);
 
        // looping through all rows and adding to list
        if (cursor.moveToFirst()) {
            do {
                DataPack d = new DataPack();
                //d.id=Integer.parseInt(cursor.getString(0));
                d.timeStamp=cursor.getString(1);
                d.magValue=(Float.parseFloat(cursor.getString(2)));
                d.lightValue=(Float.parseFloat(cursor.getString(3)));
                d.gravValue=(Float.parseFloat(cursor.getString(4)));
                d.aXValue=(Float.parseFloat(cursor.getString(5)));
                d.aYValue=(Float.parseFloat(cursor.getString(6)));
                d.aZValue=(Float.parseFloat(cursor.getString(7)));
                d.longtitude=cursor.getString(8);
                d.lattitude=cursor.getString(9);
                d.ssid=cursor.getString(10);
                d.mac=cursor.getString(11);
                d.rssi=Integer.parseInt(cursor.getString(12));
                sensorList.add(d);
            } while (cursor.moveToNext());
        }
        db.close();
        // return contact list
        return sensorList;
    }
    
    
    
 
    // Updating single contact
    public int updateContact(Contact contact) {
        SQLiteDatabase db = this.getWritableDatabase();
 
        ContentValues values = new ContentValues();
        values.put(KEY_TIME, contact.time);
        values.put(KEY_CALL, contact.call);
        values.put(KEY_SMS, contact.sms);
        // updating row
        return db.update(TABLE_CONTACTS, values, KEY_ID + " = ?",
                new String[] { String.valueOf(contact.id) });
    }
 
    // Deleting single contact
    public void deleteContact(Contact contact) {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete(TABLE_CONTACTS, KEY_ID + " = ?",
                new String[] { String.valueOf(contact.id) });
        db.close();
    }
 
    // Getting contacts Count
    public int getContactsCount() {
        String countQuery = "SELECT * FROM " + TABLE_CONTACTS;
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery(countQuery, null);
        //cursor.close();
 
        // return count
        return cursor.getCount();
    }
    
    public int getSensorsCount() {
        String countQuery = "SELECT * FROM " + TABLE_SENSOR;
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery(countQuery, null);
        //cursor.close();
 
        // return count
        return cursor.getCount();
    }
    
    public void clearContact()
    {
    	SQLiteDatabase db = this.getWritableDatabase();
    	db.delete(TABLE_CONTACTS, null, null);
    	db.close();
    }
    
    public void clearSensor()
    {
    	SQLiteDatabase db = this.getWritableDatabase();
    	db.delete(TABLE_SENSOR, null, null);
    	db.close();
    }
    
    public Contact getContact(String key,String value) 
    {    	
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_CONTACTS, new String[] { KEY_ID,
                KEY_TIME, KEY_CALL,KEY_SMS }, key + "=?",
                new String[] { value }, null, null, null, null);
        //cursor.
        if (cursor.getCount()<1)
        	return null;
        cursor.moveToFirst();
        
        Contact contact = new Contact(
        		Integer.parseInt(cursor.getString(0)),
        		cursor.getString(1), 
        		Integer.parseInt(cursor.getString(2)),
        		Integer.parseInt(cursor.getString(3))
        		);
        db.close();
        return contact;        
    }
}