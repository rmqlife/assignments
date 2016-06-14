package com.example.rmqmobile;

public  class SensorRequest {
	static final public int DATE_REQUEST=1;
	static final public int PIC_REQUEST=2;
	//final public String CHECK_USER=2;
	//final public String CHECK_CONNECT="check_connect";
	//static final public String ERROR_USER="wrong user";
	//static final public String ERROR_NO_DATA="no data";
	private String timeStamp;
	static final private String SPT="=";
	private boolean isDateRequest=false;
	private boolean isPicRequest=false;
	private String username,password;
	
	public String requestToString()
	{
		StringBuffer sb=new StringBuffer();
		sb.append(username);
		sb.append(SPT);
		sb.append(password);
		sb.append(SPT);
		if (isDateRequest)
		{
			sb.append(DATE_REQUEST);
			sb.append(SPT);
			sb.append(timeStamp);
			return sb.toString();
		}
		if (isPicRequest)
		{
			sb.append(PIC_REQUEST);
			return sb.toString();
		}
		return "no request";
	}
	
	public void requestDate(String timeStamp)
	{
		this.timeStamp=timeStamp;

		this.isDateRequest=true;
	}
	
	public boolean isDateRequest()
	{
		return isDateRequest;
	}
	public boolean isPicRequest()
	{
		return isPicRequest;
	}
	public String timeStamp()
	{
		return timeStamp;
	}
	public void requestPic()
	{		

		isPicRequest=true;
	}
	
	static public SensorRequest stringToRequest(String s)
	{
		String spl[]=s.split(SPT);
		SensorRequest sr=new SensorRequest(spl[0],spl[1]);
		
		if (Integer.parseInt(spl[2])==SensorRequest.DATE_REQUEST)
		{
			sr.isDateRequest=true;
			sr.timeStamp=spl[3];
			return sr;
		}
		
		if (Integer.parseInt(spl[2])==SensorRequest.PIC_REQUEST)
		{
			sr.isPicRequest=true;
			return sr;
		}
		return null;
	}
	
	public SensorRequest(String username,String password)
	{
		this.username=username;
		this.password=password;
	}
	
	/*
	public static void main(String args[])
	{
		SensorRequest sr=new SensorRequest("jia","123");
		sr.requestDate("2010-11-11");
		String s1=sr.requestToString();
		//System.out.println(st);
		
		SensorRequest sr2=new SensorRequest("jia","321");
		sr2.requestPic();
		String s2=sr2.requestToString();
		
		SensorRequest t1=SensorRequest.stringToRequest(s1);
		SensorRequest t2=SensorRequest.stringToRequest(s2);
		if (t1.isDateRequest())
			System.out.println(t1.timeStamp());
		if (t2.isPicRequest())
			System.out.println(t2.username+":"+t2.password);
	}
	*/
}
