import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Vector;


public class DecisionTree {
	int classCount=2;
	List<Example> samples=new ArrayList<Example>();
	DecisionNode decisionRoot;

	public Example[] divideSamples(int num)
	{
		
		Example[] v=new Example[num];
		for (int i=0;i<num;i++)
		{
			int k=(int)(Math.random()*samples.size());
			v[i]=samples.get(k);
			samples.remove(k);
		}
		return v;
	}
	
	public void reset()
	{
		decisionRoot=null;
	}
	
	public int getLayer()
	{
		return decisionRoot.getLayer();
	}
	
	public int getSize()
	{
		return decisionRoot.getSize();
	}
	
	public Example[] getFromSamples(int num)
	{
		Example[] v=new Example[num];
		for (int i=0;i<num;i++)
		{
			int k=(int)(Math.random()*samples.size());
			v[i]=samples.get(k);
		}
		return v;
	}
	
	
	
	
	public void file2samples(String filename) 
	{
		File file = new File(filename);
		try{
			if (file.isFile() && file.exists())
			{	
				InputStreamReader read = new InputStreamReader(new FileInputStream(file), "GBK");   
				BufferedReader bufferedReader = new BufferedReader(read);   
				String lineTXT = null;   
				while ((lineTXT = bufferedReader.readLine()) != null) 
				{   
					String[] a = lineTXT.split("[^a-zA-Z0-9]+");
//					System.out.print(a.length);
//					for(int i=0;i<a.length;i++)
//						System.out.print(a[i]+"?");
					Example sample=new Example();
					sample.init(a);
					samples.add(sample);
				}   
				read.close();
			}
		}catch(IOException e){
			
		}
	}

	
	void deleteUnrelated()
	{
		DecisionNode dn=decisionRoot;
		dn.clear();
	}
	
	
	void train(Example[] samples, int propertiesLength)
	{
		decisionRoot=new DecisionNode(samples,propertiesLength);
		decisionRoot.produceNode();
	}
	void clear()
	{
		decisionRoot.clear();
	}
	void prun(Example[] elist)
	{
		for (int i=0;i<elist.length;i++)
		{
			Example e=elist[i];
			this.decisionRoot.decide(e);
		}
		this.decisionRoot.prun();
	}
	
	
	
	
	static public void main(String args[])
	{
		DecisionTree dt=new DecisionTree();
		dt.file2samples("/Users/jzd/Documents/testfile/german.data");
//		System.out.println("Samples Size:"+dt.samples.size());
		
		
		Example[] testSet=dt.divideSamples(250);
		for(int i=0;i<6;i++)
		{
			Example[] trainingSet=dt.getFromSamples(250);
			dt.reset();
			dt.train(trainingSet,20);
			int k=dt.test(testSet);
			int m=dt.getLayer();
			int n=dt.getSize();
			System.out.println("ACCURACY "+k+" SIZE "+n+" LAYER "+ m);
		}
		
		
		
//		dt.prun();
		
		
//		dt.deleteUnrelated();
	}
	
	 public int test(Example[] elist)
	{
		int accept=0,reject=0;
		for (int i=0;i<elist.length;i++)
		{
			Example e=elist[i];
			if (this.decisionRoot.decide(e)==e.className)
			{
				accept++;
			}
			else
				reject++;
		}
		return accept;
	}
	
	
	public void printProperties(Property[] properties)
	{
		for (int i=0;i<properties.length;i++)
		{
			System.out.println(i+" type:"+properties[i].type+", from "
					+properties[i].rangeDown+" to "+properties[i].rangeUp+" count:"+properties[i].count);
			for (int k=0;k<properties[i].valueCount.length;k++)
			{
				System.out.print(properties[i].keys[k]+":"+properties[i].valueCount[k][0]+";"+properties[i].valueCount[k][1]+","+properties[i].valueCount[k][2]+" ");
			}
			System.out.println();
		}
	}
	
	
	
	
	
}
