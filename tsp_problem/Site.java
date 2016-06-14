
public class Site {
	String name;
	float x,y;
	Site(String name,float x,float y)
	{
		this.x=x;
		this.y=y;
		this.name=name;
	}
	Site(Site s)
	{
		this.set(s);
	}
	void print()
	{
		System.out.println(name+" "+x+" "+y);
	}
	
	void set(Site s)
	{
		this.name=s.name;
		this.x=s.x;
		this.y=s.y;
	}
	
	double dist(Site s)
	{
		return Math.sqrt((s.x-this.x)*(s.x-this.x)+(s.y-this.y)*(s.y-this.y));
	}
}
