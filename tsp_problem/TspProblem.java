import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;


public class TspProblem {
	
	List<Site> sites=new ArrayList<Site>();
	
	int siteCount=0;
	public void getInputData(String filename)
	{
		try{
			File file = new File(filename);
			int lines=0;
			if (file.isFile() && file.exists()){	
				InputStreamReader read;
				read = new InputStreamReader(new FileInputStream(file), "GBK"); 
				BufferedReader bufferedReader = new BufferedReader(read);   
				String lineTXT = null;   
				while ((lineTXT = bufferedReader.readLine()) != null) {  
					if (lines==0){
						siteCount=Integer.parseInt(lineTXT);
					}
					else{
						String[] ans=lineTXT.split("\\s");
						//for (int i=0;i<ans.length;i++)
						Site s=new Site(ans[0],Float.parseFloat(ans[1]),Float.parseFloat(ans[2]));
						sites.add(s);
					}
					//System.out.println(lineTXT);
					lines++;
				}
			}
		}
		catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}  catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		finally
		{
			
			
		}
		
	}
	
	
	
	
	
	public void find(float Tstart,float Tmin,float R,String outname) throws IOException
	{
		Solution s=new Solution(sites);
		s.countDist();
//		s.print();
//		s.next().print();
//		s.print();
		File f=new File(outname);
		BufferedWriter output = new BufferedWriter(new FileWriter(f));

		Solution bestS=new Solution(sites);
		bestS.countDist();
		float T=Tstart;
		while(T>Tmin){
			int accept=0;
			float bestAns=Float.MAX_VALUE;
			s.set(bestS);
		while(accept<100){
			if (s.dist<bestAns)
			{
				bestS.set(s);
				bestAns=s.dist;
			}
			Solution s0=s.next();
			s0.countDist();
			float dE=-(s0.dist-s.dist);
			if (dE>=0)
			{
				s.set(s0);
				accept++;
			}
			else
			{
				if (Math.exp(dE/T)>Math.random())
				{
					s.set(s0);
					accept++;
					//s=s0;
					//s.dist=s0.dist;
				}
			}
		}
			T=T*R;
			//s.countDist();
			System.out.print(T);
			s.print();
			output.write(s.print2String()+'\n');
		}
		output.close();
	}
	
	
	
	
	
	
	public void printSites(List<Site> s)
	{
		for (int i=0;i<sites.size();i++)
		{
			s.get(i).print();
		}
	}
	static public void main(String args[]) throws IOException
	{
		TspProblem tsp=new TspProblem();
		//"/Users/jzd/Documents/Course/人工智能导论/homework3/TSP10.txt"
		tsp.getInputData(args[0]);
		//"/Users/jzd/Documents/Course/人工智能导论/homework3/TSP10out.txt");
		tsp.find(280f,0.02f,0.95f,args[1]);
	}
}
