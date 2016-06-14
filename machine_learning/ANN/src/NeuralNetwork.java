import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;


public class NeuralNetwork {
	Perceptron[] hidden;
	Perceptron[] output;
	Perceptron[] input;
	List<Example> samples=new ArrayList<Example>();
	double [][] w;
	double [][] wi;
	NeuralNetwork(String filename)
	{
		initSamples(filename);
	}
	
	
	void initSamples(String filename)
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
					int[] k=new int[a.length];
					for(int i=0;i<a.length;i++){
						k[i]=Integer.valueOf(a[i]);
//						System.out.print(a[i]+"?");
					}
					Example sample=new Example(k);
					samples.add(sample);
//					System.out.print("\n");
				}   
				read.close();
			}
		}catch(IOException e){
			
		}
	}
	
	public void Backpropagation(int n_in,int n_out,int n_hidden,double speed,int sampleAmount,int times, double delta_bound){
		n_hidden++;
		n_in++;
		hidden=new Perceptron[n_hidden];
		output=new Perceptron[n_out];
		input=new Perceptron[n_in];//for bias
		for (int i=0;i<hidden.length;i++)
			hidden[i]=new Perceptron();
		for (int i=0;i<output.length;i++)
			output[i]=new Perceptron();
		for (int i=0;i<input.length;i++)
			input[i]=new Perceptron();
		input[input.length-1].out=1;
		w=new double[hidden.length][output.length];
		wi=new double[input.length][hidden.length];
		//set the initial w
		for	(int i=0;i<n_hidden;i++)
			for	(int j=0;j<n_out;j++){
//				System.out.println(i+" "+j);
				w[i][j]=Math.random()*0.1-0.1;
			}
		for	(int i=0;i<n_in;i++)
			for	(int j=0;j<n_hidden;j++)
				wi[i][j]=Math.random()*0.1-0.1;
		
		
		for (int j=0;j<times;j++)
		{
			for (int i=0;i<sampleAmount;i++)
			{
				Example s=samples.get(i);
				getOutput(s);
				getDelta(s);
				if (updateW(speed)<delta_bound){
					System.out.println("finish training at "+j);
					return;
				}
			}
		}

		System.out.println("not enough times");
	}
	
	
	
	
	
	
	void getOutput(Example sample)
	{
		
//		sample.debug();
		for (int i=0;i<sample.x.length;i++)
		{
			input[i].out=(double)sample.x[i];
		}
//		sigmoid(input,input.length); // should not
		input[input.length-1].out=1;
		
		clearOut(hidden,hidden.length);
		for (int i=0;i<input.length;i++){
			for (int j=0;j<hidden.length;j++)
				hidden[j].out+=input[i].out*wi[i][j];
		}
		
		sigmoid(hidden,hidden.length);
		hidden[hidden.length-1].out=1;
		
		clearOut(output,output.length);
		for (int i=0;i<hidden.length;i++){
			for (int j=0;j<output.length;j++)
				output[j].out+=hidden[i].out*w[i][j];
		}
		sigmoid(output,output.length);
	}
	
	
	void printOutput(Perceptron[] p)
	{
		System.out.println("print out");
		for (int i=0;i<p.length;i++)
			System.out.println(p[i].out);
	}
	
	void printTarget(Perceptron[] p)
	{
		System.out.println("print target");
		for(int i=0;i<p.length;i++)
			System.out.println(p[i].target);
	}
	
	static public double sigmoid(double y){
//		return 1/(Math.exp(-y)+1);
		return 1/(Math.pow(Math.E, -y)+1);
	}


	void sigmoid(Perceptron[] p,int length)
	{
		for (int i=0;i<length;i++)
			p[i].out=sigmoid((double)p[i].out);
	}
	void clearOut(Perceptron[] p,int length)
	{
		for (int i=0;i<length;i++)
			p[i].out=0;
	}
	
	
	void getDelta(Example sample){
		setOutputTarget(sample.target);
		for (int i=0;i<output.length;i++){
			output[i].delta=(1-output[i].out)*output[i].out*(output[i].target-output[i].out);//.getDelta();
//			output[i].delta=output[i].target-output[i].out;

		}
		for (int i=0;i<hidden.length;i++){
			double temp=0;
			for (int j=0;j<output.length;j++)
				temp+=w[i][j]*output[j].delta;
			hidden[i].delta=(1-hidden[i].out)*hidden[i].out*temp;
//			hidden[i].delta=temp;
		}

	}
	
	
	
	
	
	
	double updateW(double speed)
	{
		double max=0;
		for (int i=0;i<hidden.length;i++)
			for (int j=0;j<output.length;j++){
				double delta=speed*output[j].delta*hidden[i].out;
				w[i][j]=w[i][j]+delta;
//				if (Math.abs(delta)>max)
				if(delta>max)
					max=delta;
			}
		
		for (int i=0;i<input.length;i++)
			for (int j=0;j<hidden.length;j++){
				double delta=speed*hidden[j].delta*input[i].out;
				wi[i][j]=wi[i][j]+delta;
//				if (Math.abs(delta)>max)
				if(delta>max)
					max=delta;
			}
		
		return max;
	}
	
	void setOutputTarget(int x)
	{
		for (int i=0;i<output.length;i++)
		{
			output[i].target=0;
		}
		output[x].target=1;
	}
	
	void printMatrix(double w[][]){
		for (int i=0;i<w.length;i++)
		{
			for (int j=0;j<w[0].length;j++)
				System.out.print(w[i][j]+" ");
			System.out.println();
		}
	}
	
	void checkSigmoid()
	{	
		for (int i=-1000;i<1000;i++)
		{
			System.out.println(sigmoid((double)i/100));
		}
	}
	
	int getResult(Example sample){
		getOutput(sample);
		double max=0;
		int maxi=-1;
		for (int i=0;i<output.length;i++)
			if (output[i].out>max){
				max=output[i].out;
				maxi=i;
			}
		return maxi;
	}
	
	
	static public void main(String args[]){
		String fileIn=new String("/Users/jzd/Documents/testfile/digit.txt");
		NeuralNetwork nn=new NeuralNetwork(fileIn);
//		nn.Backpropagation(1, 2, 1, 0.7, 2, 1000);//for tease
		nn.Backpropagation(20, 10, 20, 0.05, 5000, 1000,0.0000000001);//for digit
//		nn.getOutput(nn.samples.get(4));
//		nn.printOutput(nn.output);
		System.out.println(nn.getResult(nn.samples.get(4)));
	}
}
