package com.example.rmqmobile;
import java.util.ArrayList;
import java.util.List;


public class DataPack {
	 public float magValue,lightValue,gravValue,aXValue,aYValue,aZValue;
	 public String lattitude,longtitude;
	 public  String username,password,timeStamp,ssid,mac;
	 public int rssi;
	 static private int ENCODE_MASK=10;
	 //sparate for values
	 final private String sp="%";
	 //sparate for lists
	 static final private String spl="#";
	 public static String KEY_TIMESTAMP="timestamp",KEY_MAG="mag",KEY_GRAV="grav",KEY_LIGHT="light",KEY_AX="ax",KEY_AY="ay",KEY_AZ="az",
	 KEY_LONGT="longtitude",KEY_LAT="lattitude",KEY_WIFI_SSID="ssid",KEY_WIFI_MAC="mac",KEY_WIFI_RSSI="rssi";
	 
	 public String objectToString()
	 {		
		 String r=username+sp+password+sp+timeStamp+sp+magValue+sp+lightValue+sp+gravValue
				 +sp+aXValue+sp+aYValue+sp+aZValue+sp+longtitude+sp+lattitude+sp+ssid+sp+mac+sp+rssi;

		 return r;
	 }
	 
	 
	 static public String encodeData(String r)
	 {
		 StringBuffer t=new StringBuffer(r);
		 StringBuffer s=new StringBuffer("");
		 
		 for (int i=0;i<t.length();i++)
			 {
			 char ch=t.charAt(i);
			 ch=(char)((byte)ch+(i%ENCODE_MASK));
			 s.append(ch);
			 }
		 
		 return s.toString();
	 }
	 
	 static public String decodeData(String r)
	 {
		 StringBuffer t=new StringBuffer(r);
		 StringBuffer s=new StringBuffer("");
		 for (int i=0;i<t.length();i++)
			 {
			 char ch=t.charAt(i);
			 ch=(char)((byte)ch-(i%ENCODE_MASK));
			 s.append(ch);
			 }
		 return s.toString();
	 }
	 
	 
	 public void stringToObject(String r)
	 {

		 
		 
		 
		 String spl[]=r.split(sp);
		 // to debug with
		 //for (int i=0;i<spl.length;i++)
			// System.out.println(spl[i]+"%");
		 
		 this.username=spl[0];
		 this.password=spl[1];
		 this.timeStamp=spl[2];
		 this.magValue=Float.parseFloat(spl[3]);
		 this.lightValue=Float.parseFloat(spl[4]);
		 this.gravValue=Float.parseFloat(spl[5]);
		 this.aXValue=Float.parseFloat(spl[6]);
		 this.aYValue=Float.parseFloat(spl[7]);
		 this.aZValue=Float.parseFloat(spl[8]);
		 
		 this.longtitude=spl[9];
		 this.lattitude=spl[10];
		 
		 this.ssid=spl[11];
		 this.mac=spl[12];
		 this.rssi=Integer.parseInt(spl[13]);
	 }
	 
	 
	 public DataPack(String username,String password,String timeStamp,
			 float magValue,float lightValue,float gravValue,float aXValue,float aYValue,float aZValue,
			 double longtitude,double lattitude,String ssid,String mac,int rssi)
	 {
		 this.magValue=magValue;
		 this.lightValue=lightValue;
		 this.aXValue=aXValue;
		 this.aYValue=aYValue;
		 this.aZValue=aZValue;
		 this.gravValue=gravValue;
		 this.password=password;
		 this.username=username;
		 this.timeStamp=timeStamp;
		 
		 this.longtitude=Double.toString(longtitude);
		 this.lattitude=Double.toString(lattitude);
		 this.ssid=ssid;
		 this.mac=mac;
		 this.rssi=rssi;
	 }
	 
	 public DataPack()
	 {
		 username="";
		 password="";
		 timeStamp="";
	 }
	 public DataPack(String s)
	 {
		 this.stringToObject(s);
	 }
	 
	 public List<String> getList()
	 {
		 String sq=" : ";
		 List<String> data = new ArrayList<String>();
		 data.add(KEY_TIMESTAMP+sq+this.timeStamp);
		 data.add(KEY_MAG+sq+this.magValue);
		 data.add(KEY_GRAV+sq+this.gravValue);
		 data.add(KEY_LIGHT+sq+this.lightValue);
		 data.add(KEY_LAT+sq+this.lattitude);
		 data.add(KEY_LONGT+sq+this.longtitude);
		 data.add(KEY_AX+sq+this.aXValue);
		 data.add(KEY_AY+sq+this.aYValue);
		 data.add(KEY_AZ+sq+this.aZValue);
		 data.add(KEY_WIFI_SSID+sq+this.ssid);
		 data.add(KEY_WIFI_MAC+sq+this.mac);
		 data.add(KEY_WIFI_RSSI+sq+this.rssi);
		 return data;
	 }
	 
	 static public String listToString(List<DataPack> dataList)
	 {
		 StringBuffer sb=new StringBuffer();
		 //sb.append(dataList.size());
		 //sb.append(spl);
		 for (DataPack c:dataList)
	        {
	        	String s=c.objectToString();
	        	sb.append(s+spl);
	        }
		 sb.deleteCharAt(sb.length()-1);
		 return sb.toString();
	 }
	 
	 static public List<DataPack> stringToList(String s)
	 {
		 String []splitList=s.split(spl);
		 List<DataPack> listData=new ArrayList<DataPack>();
		 //for (int i=0;i<splitList.length;i++)
			 //System.out.println(splitList[i]);
		 
		 
		 for (int i=0;i<splitList.length;i++)
		 {
			 DataPack d=new DataPack(splitList[i]);
			 listData.add(d);
		 }
		 
		 return listData;
	 }
	  

}
