
public class Property {
//	int key=0;
	int value=0;
	int rangeDown=Integer.MAX_VALUE;
	int rangeUp=Integer.MIN_VALUE;
	int type=0;
	int[][] valueCount;//
	int[] keys;//for discrete values their name to int
	int count;
	int classname;
	static  int DISCRETE=1;
	static  int CONSISTENT=2;
	int divide=0;
}
