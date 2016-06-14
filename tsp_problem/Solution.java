import java.util.ArrayList;
import java.util.List;


public class Solution {
	List<Site> sites=new ArrayList<Site>();
	Solution(List<Site> sites)
	{
		//this.sites=sites;
		for (int i=0;i<sites.size();i++)
		{
			Site ss=new Site(sites.get(i));
			this.sites.add(ss);
		}
//		this.dist=dist;
		//System.out.println(sites.size());
	}
	float dist=0;
	Solution next()
	{
		Solution s=new Solution(this.sites);
		
		int t1=(int)(Math.random()*sites.size());
		int t2=(int)(Math.random()*sites.size());
		if (t2==t1)
			t2=(t1==0)?t1+1:t1-1;
		//swap
		Site temp=new Site(s.sites.get(t1));
		s.sites.get(t1).set(s.sites.get(t2));
		s.sites.get(t2).set(temp);
		
		//System.out.println(t1+","+t2);
		return s;
	}
	String print2String()
	{
		String s="";
		if (dist==0)
			dist=countDist();
		for (int i=0;i<sites.size();i++)
			s+=sites.get(i).name+" ";
		s+=dist;
		return s;
	}
	void set(Solution s)
	{
//		this.sites=s.sites;
		for (int i=0;i<s.sites.size();i++)
			this.sites.set(i, s.sites.get(i));
		this.dist=s.dist;
	}
	
	void print()
	{
		System.out.println(print2String());
	}
	
	float countDist()
	{
		double result=0;
		for (int i=0;i<sites.size();i++)
		{
			Site s=sites.get(i);
			result+=s.dist(sites.get((i+1)%sites.size()));
		}
		dist=(float)result;
		return (float)result;
	}
}
