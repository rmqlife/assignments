package com.example.rmqmobile;



import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.apache.http.protocol.HTTP;
import org.apache.http.util.EntityUtils;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

public class NetworkActivity extends Activity 
{
	private ToggleButton toggleService;
	private EditText editIP,editPort,editName,editPassword;
	public static String EXTRA_SET_ADDRESS="com.example.rmqmobile.NetworkActivity.action.SET_IP";
	public static String IP_ADDRESS="com.example.rmqmobile.NetworkActivity.IP_ADDRESS";
	public static String EXTRA_SET_FREQUENCY="com.example.rmqmobile.NetworkActivity.SET_FREQUENCY";
	public static String EXTRA_UPLOAD_ALL_DATA="com.example.rmqmobile.NetworkActivity.UPLOAD_ALL_DATA";
	public static String EXTRA_DOWNLOAD_DATA="com.example.rmqmobile.NetworkActivity.DOWNLOAD_DATA";
	public static String EXTRA_DOWNLOAD_IN="com.example.rmqmobile.NetworkActivity.DOWNLOAD_IN";
	public static String EXTRA_DOWNLOAD_PIC="com.example.rmqmobile.NetworkActivity.DOWNLOAD_PIC";
	public static String EXTRA_UPLOAD_PIC="com.example.rmqmobile.NetworkActivity.UPLOAD_PIC";
	public static String EXTRA_TAKE_PHOTO="com.example.rmqmobile.NetworkActivity.TAKE_PHOTO";


	public static String FREQUENCY="com.example.rmqmobile.NetworkActivity.FREQUENCY";

	//private RadioGroup radioFreq;
	private RMQApplication app;


	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_network);
		editName=(EditText)findViewById(R.id.edit_name);
		editPassword=(EditText)findViewById(R.id.edit_password);
		editIP=(EditText)findViewById(R.id.edit_IP);
		editPort=(EditText)findViewById(R.id.edit_port);
		toggleService=(ToggleButton)findViewById(R.id.toggleService);      
		//radioFreq=(RadioGroup)findViewById(R.id.radioFreq);
		//editIP.setText("59.66.131.123");
		
		editPort.setText("8080");
		app=(RMQApplication)getApplication();
		editName.setText(app.userName);
		editPassword.setText(app.userPassword);
		editIP.setText(app.ipAddress);
		setToggle();		 
		//toggleService.setChecked(checked);
		//radioFreq.getCheckedRadioButtonId()
	}



	private void setToggle()
	{
		toggleService.setChecked(app.serviceRun);
	}
	public void setFreq30(View view)
	{
		Intent intent=new Intent(EXTRA_SET_FREQUENCY);
		intent.putExtra(FREQUENCY, 30);

		sendBroadcast(intent);	
	}
	public void setFreq60(View view)
	{
		Intent intent=new Intent(EXTRA_SET_FREQUENCY);
		intent.putExtra(FREQUENCY, 60);	
		sendBroadcast(intent);	
	}
	public void setFreq120(View view)
	{
		Intent intent=new Intent(EXTRA_SET_FREQUENCY);
		intent.putExtra(FREQUENCY, 120);	
		sendBroadcast(intent);	
	}

	public void uploadAll()
	{
		Intent intent=new Intent(EXTRA_UPLOAD_ALL_DATA);
		sendBroadcast(intent);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.activity_network, menu);
		return true;
	}

	public boolean checkConnect()
	{
		//Intent intent=new Intent(this,RMQMobileService.class);
		//to change user name;l
		updateIP();
		updateUserInfo();
		ConnectivityManager connMgr = (ConnectivityManager) 
				getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
		if (networkInfo != null && networkInfo.isConnected()) 
		{
			// fetch data
			//String stringUrl;
			//stringUrl=editIP.getText().toString();
			//new  DownloadWebpageText().execute(stringUrl);        
			Toast.makeText(getApplicationContext(), "connected!", Toast.LENGTH_SHORT).show();
			return true;
		} else {
			Toast.makeText(getApplicationContext(), "error:please check your connect", Toast.LENGTH_SHORT).show();
			// display error
			return false;
		}    	
	}


	public void checkConnect(View view) 
	{
		checkConnect();          	
	}    

	public void toggleService(View view)
	{   	    	
		if (toggleService.isChecked())
		{
			startService(new Intent(this, RMQMobileService.class));
			String message = editIP.getText().toString();

			Intent intent=new Intent(this,RMQMobileService.class);
			intent.putExtra(EXTRA_SET_ADDRESS, message);

			sendBroadcast(intent);

		}else 
		{
			stopService(new Intent(this, RMQMobileService.class));

		}
		app.serviceRun=toggleService.isChecked();

	}





	public void sendData(View view)
	{
		TextView resultText = (TextView) this.findViewById(R.id.show_times);                 

		String httpUrl = "http://59.66.131.123:8080/AndroidInteract/receiver"; 
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
		DataPack a=new DataPack("he","123","20100827",1,2,3,4,5,6,7,8,"afds","asfda",-3);
		params.add(new BasicNameValuePair("DataPack",a.objectToString()));
		try{ 
			//设置字符集 
			HttpEntity httpentity = new UrlEncodedFormEntity(params, HTTP.UTF_8); 		 
			//请求httpRequest 

			httpRequest.setEntity(new StringEntity(a.objectToString(), HTTP.UTF_8));
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
				resultText.setText(strResult); 
			}else
			{ 
				resultText.setText("请求错误!"); 
			} 
		}catch (ClientProtocolException e){ 
			resultText.setText(e.getMessage().toString()); 
		} catch (IOException e){ 
			resultText.setText(e.getMessage().toString()); 
		}catch (Exception e){ 
			resultText.setText(e.getMessage().toString()); 
		}  
	}


	public void updateUserInfo()
	{
		app.userName=editName.getText().toString();
		app.userPassword=editPassword.getText().toString();
	}
	private void updateIP()
	{
		String s="http://"+editIP.getText().toString()+":"+editPort.getText().toString();
		app.ipAddress=s;
		Intent intent=new Intent(EXTRA_SET_ADDRESS);
		//intent.putExtra(IP_ADDRESS, s);
		sendBroadcast(intent);
		
		//return s;
	}
	
	
}
