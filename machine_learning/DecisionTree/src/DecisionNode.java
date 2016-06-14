import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Vector;


public class DecisionNode {
	Property decision;
	double infoGain=0;
	int key;//WHICH KEY THIS NODE IS LOOKING AT
	int value;//WHICH VALUE CAN GO TO THIS NODE
	public Example[] samples;//=new Vector<Example> ();
	Vector<DecisionNode> cNode=new Vector<DecisionNode>();//child node
	private boolean[] availProperties;
	boolean isLeaf=false;
	private int className;
	private int layer=0;
	private int []amount=new int[3];
	public int acceptThis=0,rejectThis=0;
	public int acceptChild=0,rejectChild=0;
	
	public int getSize()
	{
		if (this.isLeaf)
			return 1;
		else{
			int k=0;
			for (int i=0;i<this.cNode.size();i++)
			{
				k=k+this.cNode.get(i).getSize();
			}
			return k;
		}	
	}
	
	public int getLayer()
	{
		if (this.isLeaf)
			return this.layer;
		else{
			int k=0;
			for (int i=0;i<this.cNode.size();i++)
			{
				int m=this.cNode.get(i).getLayer();
				if (m>k)
					k=m;
			}
			return k;
		}
	}
	
	public void prun()
	{
		if (this.isLeaf)
			return;
		if (this.acceptThis>this.acceptChild)
		{
			this.isLeaf=true;
			System.out.println("prun!!");
		}
		else{
			for (int i=0;i<this.cNode.size();i++)
				this.cNode.get(i).prun();
		}
		
	}
	
	
	
	public void clear()
	{
		samples=new Example[0];
		availProperties=null;
		acceptThis=0;
		rejectThis=0;
		acceptChild=0;
		rejectChild=0;
//		decision=null;
		if (isLeaf)
		{
			cNode.clear();
			return;
		}
		
		for (int i=0;i<cNode.size();i++)
		{
			cNode.get(i).clear();
		}
	}
	
	
	private DecisionNode(boolean[] availP){ //for those not root
		availProperties=availP.clone();
		
	}
	
	
	public DecisionNode(Example[] sList,int propertiesLength)//only for root
	{
		availProperties=new boolean[propertiesLength];
		for(int i=0;i<availProperties.length;i++)
			availProperties[i]=true;
		Property[] p=basicTrain(sList,availProperties);
		samples=sList;
		this.getAmount();
	}
	
	private double getDecision()
	{
		assert (samples.length>0);
		Property[] p=basicTrain(samples,availProperties);
//		printProperties(p);
		return getDecisionUseP(p);
	}
	
	
	private double getDecisionUseP(Property[] p) //generalize a decision
		{
			Example[] sList=samples;
			double original=entropy(amount);
			
	//		for(int i=0;i<3;i++)
	//			System.out.println("amount"+i+":"+amount[i]);
	//		printProperties(p);
			double []temp=new double[p.length];
			int []a0=new int[3];
			int []a1=new int[3];
			double maxtemp=-Double.MAX_VALUE;
			int maxi=-1;
			for	(int i=0;i<p.length;i++)//each property
			{
				if (!this.availProperties[i]) //not avail
					continue;//this property is not available(used before)
				
				if (p[i].type==Property.CONSISTENT)
				{
					temp[i]=-Double.MAX_VALUE;
					int []a=new int[p[i].valueCount[0].length];
					int []b=new int[a.length];
					double m=0;
					
					
					for (int j=0;j<p[i].keys.length;j++)//compute the keylength's information gain and find a max
					{
						//sth<=p[i].keys[j]  sth>p[i].keys[j]
						for(int k=0;k<a.length;k++){
							a[k]=a[k]+p[i].valueCount[j][k];
							b[k]=amount[k]-a[k];
						}
						m=original-((double)a[0]/amount[0])*entropy(a)-((double)b[0]/amount[0])*entropy(b);
						if (m>temp[i]){
							temp[i]=m;
							p[i].divide=p[i].keys[j];
							a0=a;
							a1=b;
	//						System.out.println(j);
						}
					} 
				}
				else{// DISCRETE
					temp[i]=original;
					for (int j=0;j<p[i].keys.length;j++)
						temp[i]=temp[i]-((double)p[i].valueCount[j][0]/sList.length)// S_v/S
								*entropy(p[i].valueCount[j]);
				}
				
				
				if (temp[i]>maxtemp)
				{
					maxtemp=temp[i];
					maxi=i;
				}
	//			if (p[i].type==Property.CONSISTENT)
	//				System.out.println("divide: "+p[i].divide);
	//			System.out.println(i+": "+temp[i]);
			}
	//		System.out.println(maxtemp+" : "+maxi);
			this.decision=new Property();
			this.decision=p[maxi];
			this.key=maxi;
			
			this.availProperties[maxi]=false;
	//		this.infoGain=this.infoGain-maxtemp;
			return maxtemp;
		}


	//	
	private boolean haveDecision()
	{
		for (int i=0;i<this.availProperties.length;i++)
			if (this.availProperties[i])
				return true;
		return false;
	}
	
	private boolean ableExtend()
	{
//		getAmount();
		return (amount[0]>0) && (amount[1]>0) && (amount[2]>0);
	}
	
				
	private void getAmount()
	{
		for (int i=0;i<samples.length;i++)
		{
			amount[samples[i].className]++;
		}
		amount[0]=samples.length;
	}
	
	
	
	
	private void extendNode()
	//divide those samples and get some new Node
	{
		//already get the decision
		
		DecisionNode []ds;
		if (decision.type==Property.DISCRETE)
		{
			
			Comparator<Example> cmp=new ExampleComparator(this.key);
			Arrays.sort(this.samples,cmp);
			
			ds=new DecisionNode[decision.keys.length];
			for (int i=0;i<ds.length;i++){
				ds[i]=new DecisionNode(availProperties);
				ds[i].value=decision.keys[i];
				ds[i].amount=decision.valueCount[i];
				ds[i].samples=new Example[ds[i].amount[0]];
			}
			int length=0;
			//sort this
			int s0=-1,tempi=-1;
			for (int i=0;i<samples.length;i++)
			{
				int s=samples[i].attributes[key].value;
				if (s!=s0)
				{
					length=0;
					for (int j=0;j<ds.length;j++)
						if (ds[j].value==s){
							tempi=j;
						}
					s0=s;
				}
				ds[tempi].samples[length]=samples[i];
				length++;
			}
		}else
		{
			ds=new DecisionNode[2];
			ds[1]=new DecisionNode(availProperties);
			ds[0]=new DecisionNode(availProperties);
			
			Vector<Example> v1=new Vector<Example> ();
			Vector<Example> v0=new Vector<Example> ();
			int length1=0,length2=0;
			for (int i=0;i<samples.length;i++)
			{
				int s=samples[i].attributes[key].value;
				if (s>decision.divide){
					v1.add(samples[i]);
				}
				else{
					v0.add(samples[i]);
				}
			}
			ds[1].samples=new Example[v1.size()];
			ds[0].samples=new Example[v0.size()];
			for (int i=0;i<v1.size();i++)
			{
				ds[1].samples[i]=v1.get(i);
			}
			for (int i=0;i<v0.size();i++)
			{
				ds[0].samples[i]=v0.get(i);
			}
			ds[1].getAmount();
			ds[0].getAmount();
		}
		
		for (int i=0;i<ds.length;i++)
		{
			if (ds[i].samples.length>0){
				cNode.add(ds[i]);
			}
		}
			
	}
	
	
	public void printAvail()
	{
		for (int i=0;i<this.availProperties.length;i++)
		{
			System.out.print(this.availProperties[i]+" ");
		}
		System.out.println();
	}
	
	public void produceNode()
	{
		this.infoGain=entropy(this.amount);
		getDecision();
		
		if (this.amount[1]>this.amount[2])
			this.className=1;
		else
			this.className=2;
//		print();
		if (this.haveDecision() && this.ableExtend())
		{
			this.extendNode();
			for (int i=0;i<this.cNode.size();i++)
			{
				DecisionNode d=cNode.get(i);
				d.layer=this.layer+1;
				d.produceNode();
			}
		}else
		{
			this.isLeaf=true;
//			System.out.println("finish this branch");
		}
		

	}
	
	static public double entropy(int[] h)//ans should be between[0.0,1.0]
	{
		assert(h.length>=3);
		double ans=0;
		for(int i=1;i<3;i++)
		{
			if (h[i]==0)//entropy=0;
				continue;
			double p=(double)h[i]/(h[1]+h[2]);
			ans=ans-p*Math.log10(p)/Math.log10(2);
		}
		return ans;
	}
	
	
	public void printProperties(Property[] properties)
	{
		for (int i=0;i<properties.length;i++)
		{
			if (!availProperties[i])
				continue;
			System.out.println(i+" type:"+properties[i].type+", from "
					+properties[i].rangeDown+" to "+properties[i].rangeUp+" count:"+properties[i].count);
			for (int k=0;k<properties[i].valueCount.length;k++)
			{
				System.out.print(properties[i].keys[k]+":"+properties[i].valueCount[k][0]+";"+properties[i].valueCount[k][1]+","+properties[i].valueCount[k][2]+" ");
			}
			System.out.println();
		}
	}
	
	static public Property[] basicTrain(Example[] elist,boolean[] avail)
	//通过计算一组样本，得到每个属性的统计信息
	{
		Property[] properties;
		properties=new Property[elist[0].attributes.length];
//		System.out.print(properties.length);
		for (int i=0;i<properties.length;i++){
			properties[i]=new Property();
			properties[i].type=elist[0].attributes[i].type;
		}		
		for (int j=0;j<properties.length;j++){
			if (!avail[j] )//use this properties before
				continue;
			Comparator<Example> cmp=new ExampleComparator(j);
			Arrays.sort(elist,cmp);
			int length=0,s0=-1,s,num=-1;
			Property temp=new Property();
			
			temp.keys=new int[elist.length];
			temp.valueCount=new int[elist.length][3];
			for (int i=0;i<elist.length;i++){
				s=elist[i].attributes[j].value;
				if (s!=s0){
					s0=s;
					length=0;
					num++;
				}
				temp.keys[num]=s;
				temp.valueCount[num][0]++;
				temp.valueCount[num][elist[i].className]++;
			}
			
			num++;
			properties[j].keys=new int[num];
			properties[j].valueCount=new int[num][3];
			for (int i=0;i<num;i++)
			{
				properties[j].keys[i]=temp.keys[i];
				properties[j].valueCount[i]=temp.valueCount[i];
			}
		}
		
		return properties;
	}
	
	public void print()
	{
		String s=new String();
		s=s+" LAYER "+this.layer;
		s=s+" KEY "+key;
		if (this.decision.type==Property.CONSISTENT)
			s=s+" DIV "+this.decision.divide;
		else
			s=s+" VALUE "+this.value;
		s=s+" SAMPLES "+this.amount[0];
		s=s+" CLASS "+this.className;
		System.out.println(s);
	}
	
	
	public int decide(Example e)
	{
		if (e.className==this.className)
			this.acceptThis++;
		else
			this.rejectThis++;
		
		
		if (this.isLeaf)
			return this.className;
		else{
				if (this.decision.type==Property.CONSISTENT){
					if (e.attributes[this.key].value>this.decision.divide)
					{
						int r=this.cNode.get(1).decide(e);
						if (r==e.className)
							this.acceptChild++;
						else
							this.rejectChild++;
						return r;
					}
					else{
						int r=this.cNode.get(0).decide(e);
						if (r==e.className)
							this.acceptChild++;
						else
							this.rejectChild++;
						return r;
					}
				}
				else{
					for (int i=0;i<this.cNode.size();i++)
					{
						if (this.cNode.get(i).value==e.attributes[this.key].value){
							int r= this.cNode.get(i).decide(e);
							if (r==e.className)
								this.acceptChild++;
							else
								this.rejectChild++;
							return r;
						}
					}
				}
			
		}
		return -1;	
	}
	
	
	
	
	
}
