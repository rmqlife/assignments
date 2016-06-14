
public class Example {
	public int[] x;
	public int target;
	Example(int[] k)
	{
		target=k[0];
		x=new int[k.length-1];
		for(int i=1;i<k.length;i++)
			x[i-1]=k[i];
	}
	void debug()
	{
		System.out.println("example debug");
		System.out.print(target+" ");
		for (int i=0;i<x.length;i++)
			System.out.print(x[i]+" ");
	}
	
}
