
public class Perceptron {
	double out;
	double target;
	double delta;
	
	double getDelta()
	{
		return out*(1-out)*(target-out);
	}
	
	double getOutput(double w[],double x[])
	{
		assert(w.length==x.length);
		double out=0;
		for(int i=0;i<w.length;i++)
		{
			out=out+w[i]*x[i];
		}
		return out;
	}
	double getOutput(double w[],int x[])
	{
		assert(w.length==x.length);
		double out=0;
		for(int i=0;i<w.length;i++)
		{
			out=out+w[i]*(double)x[i];
		}
		return out;
	}
}
