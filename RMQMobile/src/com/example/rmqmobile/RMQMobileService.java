package com.example.rmqmobile;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.FileEntity;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.apache.http.protocol.HTTP;
import org.apache.http.util.EntityUtils;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.hardware.SensorManager;
import android.location.LocationManager;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Environment;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.widget.Toast;

public class RMQMobileService extends Service
{
	final private String PHONE_STATE="android.intent.action.PHONE_STATE";
    final private String SMS_RECEIVE="android.provider.Telephony.SMS_RECEIVED";
    private static final String SMS_RECEIVED = "android.provider.Telephony.SMS_RECEIVED";
    
    
    //database
    final private int ERROR_LENTH=20;
    final private int DEFAULT_FREQUENCY=30;
    private DatabaseHandler database;
    private static Timer timer;// = new Timer();
    private LocationGet locationfinder;
    //private int timerRate;
    private RMQSensor rmqsensor;
    //notificaiton
    NotificationManager mNotificationManager;
    private static final int NOTIFICATION_SERVICE_ID = 1;
    private RMQApplication app;
    private String ipAddress;
    private int totalCall=0,offhookCall=0,countSMS=0;
    final private String RECEIVER="/Android/receiver";
    final private String SENDER="/Android/sender";
    final private String PICTURE="/Android/picture";

    public IBinder onBind(Intent arg0) 
    {
          return null;
    }

    private void updateCall()
    {
    	String timestamp=TimeStamp.getDate();
    	Contact find=database.getContact(Contact.TIME, timestamp);
    	if (find==null)
    	{
    		database.addContact(new Contact(timestamp,1,0));
    		return;
    	}
    	find.call++;
    	database.updateContact(find);
    	
    	
    	find=database.getContact(Contact.TIME, Contact.TOTAL);
    	if (find==null)
    	{
    		database.addContact(new Contact(Contact.TOTAL,1,0));
    		return;
    	}
    	find.call++;
    	database.updateContact(find);
    }
    
    private void updateSMS()
    {
    	String timestamp=TimeStamp.getDate();
    	Contact find=database.getContact(Contact.TIME, timestamp);
    	if (find==null)
    	{
    		database.addContact(new Contact(timestamp,0,1));
    		return;
    	}
    	find.sms++;
    	database.updateContact(find);
    	
    	
    	find=database.getContact(Contact.TIME, Contact.TOTAL);
    	if (find==null)
    	{
    		database.addContact(new Contact(Contact.TOTAL,0,1));
    		return;
    	}
    	find.sms++;
    	database.updateContact(find);
    }
    
    LocationManager locMan;
    public void onCreate() 
    {
          super.onCreate();
          setupNotification();
          //set the database
          database = new DatabaseHandler(this);
          //set the receiver
          setupReceiver();
          app=(RMQApplication)getApplication();
          SensorManager sm=(SensorManager)getSystemService(SENSOR_SERVICE);
          LocationManager locMan = (LocationManager)getSystemService(Context.LOCATION_SERVICE);  
          
          rmqsensor=new RMQSensor(sm,locMan);
          locationfinder=new LocationGet(locMan);
          locationfinder.setTimer(DEFAULT_FREQUENCY);
          setupTimer(DEFAULT_FREQUENCY);
    }
    
    private void setupTimer(int frequency)//get data per X minutes
    {
    	timer=new Timer();
        timer.scheduleAtFixedRate(new mainTask(), 0, 1000*60*frequency);
    }
    
    
    private void setTimer(int frequency)//get data per X minutes
    {
    	timer.purge();
    	timer.cancel();
    	timer=new Timer();
        timer.scheduleAtFixedRate(new mainTask(), 0, 1000*60*frequency);
    }
    
    public void setupReceiver()
    {   

        IntentFilter ipFilter = new IntentFilter(NetworkActivity.EXTRA_SET_ADDRESS);      
        IPReceiver ipReceiver = new IPReceiver();
        registerReceiver(ipReceiver, ipFilter);
        ipFilter = new IntentFilter(NetworkActivity.EXTRA_SET_FREQUENCY);
        registerReceiver(ipReceiver, ipFilter);
        ipFilter = new IntentFilter(NetworkActivity.EXTRA_UPLOAD_ALL_DATA);
        registerReceiver(ipReceiver, ipFilter);
        ipFilter = new IntentFilter(NetworkActivity.EXTRA_DOWNLOAD_DATA);
        registerReceiver(ipReceiver, ipFilter);
        ipFilter = new IntentFilter(NetworkActivity.EXTRA_DOWNLOAD_PIC);
        registerReceiver(ipReceiver, ipFilter);
        ipFilter = new IntentFilter(NetworkActivity.EXTRA_UPLOAD_PIC);
        registerReceiver(ipReceiver, ipFilter);
        ipFilter = new IntentFilter(MainActivity.EXTRA_COLLECT_SEND);
        registerReceiver(ipReceiver, ipFilter);
        
        
        ipFilter = new IntentFilter(PHONE_STATE);
        registerReceiver(ipReceiver, ipFilter);
        ipFilter = new IntentFilter(SMS_RECEIVE);
        registerReceiver(ipReceiver, ipFilter);
        
    }
 

    
    public class IPReceiver extends BroadcastReceiver
    {
    	
		@Override
		public void onReceive(Context context, Intent intent) 
		{
			if (intent.getAction().equals(PHONE_STATE))
			{
				String state=intent.getStringExtra(TelephonyManager.EXTRA_STATE);		
				Log.d("state",state); 
				if (state.equals(TelephonyManager.EXTRA_STATE_RINGING))
				{
					//no use!
					totalCall++;
					Log.d("total",totalCall+"/");
				}
				if (state.equals(TelephonyManager.EXTRA_STATE_OFFHOOK))
				{
					offhookCall++;
					Log.d("offhook",offhookCall+"/");
					updateCall();
				}
				if (state.equals(TelephonyManager.EXTRA_STATE_IDLE))
				{}
				
				
			}
			if(intent.getAction().equals(SMS_RECEIVE))
			{
				if (intent.getAction().equals(SMS_RECEIVED)) 
					countSMS++;
				updateSMS();
			}
			
			if(intent.getAction().equals(NetworkActivity.EXTRA_SET_ADDRESS))
				ipAddress=app.ipAddress;
			
			if (intent.getAction().equals(NetworkActivity.EXTRA_SET_FREQUENCY))
				{
				int frequency=intent.getIntExtra(NetworkActivity.FREQUENCY, 0);
				Toast.makeText(getApplicationContext(), String.valueOf(frequency), Toast.LENGTH_SHORT).show();
				setTimer(frequency);
				}
			if (intent.getAction().equals(MainActivity.EXTRA_COLLECT_SEND))
			{
				//collect and send 
				DataPack d=collectData();
				database.addSensor(d);
				sendDataPack(d);				
			}
			if (intent.getAction().equals(NetworkActivity.EXTRA_UPLOAD_ALL_DATA))
			{
				uploadAllData();
			}
			if (intent.getAction().equals(NetworkActivity.EXTRA_DOWNLOAD_DATA))
			{
				String date=intent.getStringExtra(NetworkActivity.EXTRA_DOWNLOAD_IN);
				downloadData(date);
			}
			if (intent.getAction().equals(NetworkActivity.EXTRA_DOWNLOAD_PIC))
			{
				downloadPicture();
			}
			if (intent.getAction().equals(NetworkActivity.EXTRA_UPLOAD_PIC))
			{
				uploadPicture();
			}
		}
    }
    
    
    private void downloadData(String date)
    {
    	SensorRequest sr=new SensorRequest(app.userName,app.userPassword);
    	sr.requestDate(date);
    	String s=sr.requestToString();
    	String result=sendData(s,SENDER);
    	if (result.length()>ERROR_LENTH)
    	{
    		List<DataPack> datalist;//=new ArrayList<DataPack>();
    		datalist=DataPack.stringToList(result);
    		handleData(datalist);
    		return;    				
    	}
    	else
    	Toast.makeText(getApplicationContext(), result, Toast.LENGTH_LONG).show();
    }

    private class mainTask extends TimerTask
    { 
        public void run() 
        {
            //Intent intent=new Intent(RMQService)
        	//toastHandler.sendEmptyMessage(0);
        	DataPack d=collectData();
        	database.addSensor(d);
        }
    }    

    public void onDestroy() 
    {
          super.onDestroy();
          timer.cancel();
          rmqsensor.cancel();
          Toast.makeText(this, "Service Stopped ...", Toast.LENGTH_SHORT).show();
          mNotificationManager.cancel(NOTIFICATION_SERVICE_ID);
    }

    
    private final Handler toastHandler = new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {
        	Toast.makeText(getApplicationContext(), String.valueOf(countSMS), Toast.LENGTH_SHORT).show();
        	
        	//Toast.makeText(getApplicationContext(), ipAddress, Toast.LENGTH_SHORT).show();
        	//Toast.makeText(getApplicationContext(), String.valueOf(rmqsensor.gravValue), Toast.LENGTH_SHORT).show();
            //Log.d("service","test");
        }
    };

    
    
    
    private DataPack collectData()
    {
    	//this procedure should have enough time to get data
    	rmqsensor.start();

    	Log.d("datapack","collect");
    	Log.d("timestamp",TimeStamp.getTimeStamp());
    	String timestamp=TimeStamp.getTimeStamp();
    	
    	//locationfinder.start();
    	double lat=locationfinder.location.getLatitude();//getLocation().getLatitude();
    	double longt=locationfinder.location.getLongitude();//getLocation().getLongitude();
    	//locationfinder.cancel();
    	
    	WifiManager wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);  
    	WifiInfo info = wifi.getConnectionInfo();    
    	
    	
    	
    	DataPack d=new DataPack("none","none",timestamp,
    			rmqsensor.magValue,rmqsensor.lightValue,rmqsensor.gravValue,
    			rmqsensor.aXValue,rmqsensor.aYValue,rmqsensor.aZValue,longt,lat,
    			info.getSSID(),info.getMacAddress(),info.getRssi());
    	
    	//DataPack a=new DataPack("he","123","20100827",1,2,3,4,5,6);

    	//DataPack d=new DataPack();
    	
    	Log.d("datapack","toAdd");
    	
    	rmqsensor.cancel();
    	
    	return d;
    }
    
    
	private void setupNotification()
	{
		 String ns = Context.NOTIFICATION_SERVICE;
		 mNotificationManager = (NotificationManager) getSystemService(ns);
		 int icon = R.drawable.ic_action_search;
		 CharSequence tickerText = "Start RMQMobileService";
		 long when = System.currentTimeMillis();
		 
		 Notification notification = new Notification(icon, tickerText, when);
		 Context context = getApplicationContext();
		 CharSequence contentTitle = "RMQMobile";
		 CharSequence contentText = "Service is Running";
		 Intent notificationIntent = new Intent(this, MainActivity.class);
		 PendingIntent contentIntent = PendingIntent.getActivity(this, 0, notificationIntent, 0);
		 notification.setLatestEventInfo(context, contentTitle, contentText, contentIntent);
		 notification.flags=Notification.FLAG_ONGOING_EVENT;
		 mNotificationManager.notify(NOTIFICATION_SERVICE_ID, notification);
	}
	
	
	
	public void sendDataPack(DataPack datapack)
	{
		datapack.username=app.userName;
		datapack.password=app.userPassword;
		List<DataPack> datapackList =new ArrayList<DataPack>();
		datapackList.add(datapack);
		String resultText=sendData(DataPack.listToString(datapackList),RECEIVER);
	    Toast.makeText(getApplicationContext(), resultText, Toast.LENGTH_LONG).show();
	    //return resultText;
	}
	
	
	public void handleData(List<DataPack> datalist)
	{
		//TODO receive data
		Toast.makeText(getApplicationContext(),datalist.size()+" datapack(s) received", Toast.LENGTH_LONG).show();
		for (DataPack data:datalist)
		{
			database.addSensor(data);
		}
	}
	
	
	
	
	public void uploadAllData()
	{
		List<DataPack> datapackList =database.getAllSensors();
		for (DataPack c:datapackList)
		{
			c.username=app.userName;
			c.password=app.userPassword;
		}
		String s=DataPack.listToString(datapackList);
		String resultText=sendData(s,RECEIVER);
	    Toast.makeText(getApplicationContext(), resultText, Toast.LENGTH_LONG).show();
	    //TODO clear?
	    if (resultText.contains("Send"))
	    	database.clearSensor();
	}
	
	
	public String sendData(String dataPost,String dest)
	{
		//TextView resultText = (TextView) this.findViewById(R.id.show_times);                 
		String resultText;
	    String httpUrl = ipAddress+dest; 
	    //创建httpRequest对象 
	    HttpPost httpRequest = new HttpPost(httpUrl); 		          
	    
	    int TIMEOUT_MILLISEC = 10000;  // = 10 seconds
	    HttpParams httpParams = new BasicHttpParams();
	    HttpConnectionParams.setConnectionTimeout(httpParams, TIMEOUT_MILLISEC);
	    HttpConnectionParams.setSoTimeout(httpParams, TIMEOUT_MILLISEC);

	    
	    List<NameValuePair> params = new ArrayList<NameValuePair>(); 
	    //String username="username"; 
	    //String password="password";
	    //params.add(new BasicNameValuePair("username", username)); 
	    //params.add(new BasicNameValuePair("password", password));
	    //DataPack a=new DataPack("he","123","20100827",1,2,3,4,5,6,7,8,"afds","asfda",-3);
	    //params.add(new BasicNameValuePair("DataPack",datapack.objectToString()));
	    try{ 
	        //设置字符集 
	    	HttpEntity httpentity = new UrlEncodedFormEntity(params, "gb2312"); 		 
	        //请求httpRequest 
	    	
	    	httpRequest.setEntity(new StringEntity(dataPost, HTTP.UTF_8));
	        //httpRequest.setEntity(httpentity);		            
	        //取得默认的HttpClient 
	        HttpClient httpclient = new DefaultHttpClient();
	        
	        //取得HttpResponse 
	        HttpResponse httpResponse = httpclient.execute(httpRequest); 		 
	        //HttpStatus.SC_OK表示连接成功 
	        if (httpResponse.getStatusLine().getStatusCode() == HttpStatus.SC_OK)
	        { 
	            //取得返回的字符串 
	            String strResult = EntityUtils.toString(httpResponse.getEntity()); 
	            resultText=strResult; 
	        }else
	        { 
	            resultText="请求错误!"; 
	        } 
	    }catch (ClientProtocolException e)
	    { 
	    	resultText=e.getMessage().toString(); 
	    } catch (IOException e)
	    { 
	        resultText=e.getMessage().toString(); 
	    }catch (Exception e){ 
	        resultText=e.getMessage().toString(); 
	    }
	    //Toast.makeText(getApplicationContext(), resultText, Toast.LENGTH_LONG).show();
	    return resultText;
	}
	
	private void downloadPicture()
	{
		SensorRequest sr=new SensorRequest(app.userName,app.userPassword);
		sr.requestPic();
		//String result=sendData(sr.requestToString(),SENDER);
		//handlePicture(result);
		receivePic(sr.requestToString(),SENDER);
	}
	
	private void uploadPicture()
	{
		String imageFilePath = Environment.getExternalStorageDirectory().getAbsolutePath()+
				  "/RMQMobile/simbol.jpg";
		File file=new File(imageFilePath);
		if (!file.exists())
		{
			Toast.makeText(getApplicationContext(), "Picture is not available", Toast.LENGTH_LONG).show();
			return;
		}
		sendFile(file,PICTURE);
	}
	/*private void handlePicture(String str)
	{
		Toast.makeText(getApplicationContext(), str, Toast.LENGTH_LONG).show();
		InputStream is=new ByteArrayInputStream(str.getBytes());
		Bitmap bitmap = BitmapFactory.decodeStream(is);
		String imageFilePath = Environment.getExternalStorageDirectory().getAbsolutePath()+
				  "/RMQMobile/OnlinePicture1.jpg";
		try {
		       FileOutputStream out = new FileOutputStream(imageFilePath);
		       bitmap.compress(Bitmap.CompressFormat.JPEG, 90, out);
		       out.close();
		} catch (Exception e) {
		       e.printStackTrace();
		}
	}*/
	
	public void receivePic(String dataPost,String dest)
	{
		//TextView resultText = (TextView) this.findViewById(R.id.show_times);                 
	    String resultText=null;
		String httpUrl = ipAddress+dest; 
	    //创建httpRequest对象 
	    HttpPost httpRequest = new HttpPost(httpUrl); 		          
	    int TIMEOUT_MILLISEC = 10000;  // = 10 seconds
	    HttpParams httpParams = new BasicHttpParams();
	    HttpConnectionParams.setConnectionTimeout(httpParams, TIMEOUT_MILLISEC);
	    HttpConnectionParams.setSoTimeout(httpParams, TIMEOUT_MILLISEC);
	   	    try{ 
	        //设置字符集 
	    	httpRequest.setEntity(new StringEntity(dataPost, HTTP.UTF_8));
	        HttpClient httpclient = new DefaultHttpClient();	    
	        HttpResponse httpResponse = httpclient.execute(httpRequest); 		 
	        //HttpStatus.SC_OK表示连接成功 
	        if (httpResponse.getStatusLine().getStatusCode() == HttpStatus.SC_OK)
	        { 
	            HttpEntity httpEntity = httpResponse.getEntity();    
                InputStream is = httpEntity.getContent();
                Bitmap bitmap = BitmapFactory.decodeStream(is);
                is.close();
                String imageFilePath = Environment.getExternalStorageDirectory().getAbsolutePath()+
                		"/RMQMobile/simbol.jpg";
                FileOutputStream out = new FileOutputStream(imageFilePath);
                bitmap.compress(Bitmap.CompressFormat.JPEG, 90, out);
                out.close();
        		
	        }else
	        { 
	            resultText="请求错误!"; 
	        } 
	    }catch (ClientProtocolException e)
	    { 
	    	resultText=e.getMessage().toString(); 
	    } catch (IOException e)
	    { 
	        resultText=e.getMessage().toString(); 
	    }catch (Exception e){ 
	        resultText=e.getMessage().toString(); 
	    }
	   	if (resultText==null)
	   		Toast.makeText(getApplicationContext(), "Load Successfully!", Toast.LENGTH_LONG).show();
	   	else
	   		Toast.makeText(getApplicationContext(), resultText, Toast.LENGTH_LONG).show();
	}
	
	
	public void sendFile(File file,String dest)
	{
		//TextView resultText = (TextView) this.findViewById(R.id.show_times);                 
	    String resultText=null;
		String httpUrl = ipAddress+dest; 
	    //创建httpRequest对象 
	    HttpPost httpRequest = new HttpPost(httpUrl);
	    httpRequest.addHeader("username", app.userName);
	    httpRequest.addHeader("password", app.userPassword);
	    int TIMEOUT_MILLISEC = 10000;  // = 10 seconds
	    HttpParams httpParams = new BasicHttpParams();
	    HttpConnectionParams.setConnectionTimeout(httpParams, TIMEOUT_MILLISEC);
	    HttpConnectionParams.setSoTimeout(httpParams, TIMEOUT_MILLISEC);
	   	    try{ 
	        //设置字符集
	   	    FileEntity entity = new FileEntity(file,"binary/octet-stream");  
	   	    //entity.setContentEncoding("binary/octet-stream"); 
	    	httpRequest.setEntity(entity);
	        HttpClient httpclient = new DefaultHttpClient();	    
	        HttpResponse httpResponse = httpclient.execute(httpRequest); 		 
	        
            //HttpStatus.SC_OK表示连接成功 
	        if (httpResponse.getStatusLine().getStatusCode() == HttpStatus.SC_OK)
	        { 
	        	 String strResult = EntityUtils.toString(httpResponse.getEntity()); 
		         resultText=strResult; 
	        }else
	        { 
	            resultText="请求错误!"; 
	        } 
	    }catch (ClientProtocolException e)
	    { 
	    	resultText=e.getMessage().toString(); 
	    } catch (IOException e)
	    { 
	        resultText=e.getMessage().toString(); 
	    }catch (Exception e){ 
	        resultText=e.getMessage().toString(); 
	    }
	   	if (resultText==null)
	   		Toast.makeText(getApplicationContext(), "Load Successfully!", Toast.LENGTH_LONG).show();
	   	else
	   		Toast.makeText(getApplicationContext(), resultText, Toast.LENGTH_LONG).show();
	}
}
