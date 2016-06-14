import java.util.Comparator;



public class Example {
	
	
	
	public void init(String[] s)
	{
		int propertyCount=s.length-1;
		attributes=new Property[propertyCount];
		assert(s.length==propertyCount);
		for(int i=0;i<propertyCount;i++)
		{
			if (s[i].length()==0)
				continue;
			attributes[i]=new Property();
			if (s[i].charAt(0)=='A'){
				attributes[i].value=Integer.valueOf(s[i].substring(1)).intValue();
				attributes[i].type=Property.DISCRETE;
			}else{
				attributes[i].value=Integer.valueOf(s[i]).intValue();
				attributes[i].type=Property.CONSISTENT;
			}
		}
		className=Integer.valueOf(s[propertyCount]).intValue();
	}
	Property[] attributes;
	int className=0;//to be classified
}

class ExampleComparator implements Comparator<Example>
{
	public  ExampleComparator(int k)
	{
		cmpk=k;
	}
	int cmpk=0;
	
	@Override
	public int compare(Example e0, Example e1) {
		// TODO Auto-generated method stub
		if (e0.attributes[cmpk].value<e1.attributes[cmpk].value)
			return -1;
		if (e0.attributes[cmpk].value==e1.attributes[cmpk].value)
			return 0;
		if (e0.attributes[cmpk].value>e1.attributes[cmpk].value)
			return 1;
		return 0;
	}
	
}
