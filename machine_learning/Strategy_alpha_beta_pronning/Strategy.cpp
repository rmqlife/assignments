#include <iostream>
#include "Point.h"
#include "Strategy.h"
#include <conio.h>
#include <atlstr.h>

#define MIN_INT -100000
#define MAX_INT 100000
using namespace std;

/*
	���Ժ����ӿ�,�ú������Կ�ƽ̨����,ÿ�δ��뵱ǰ״̬,Ҫ�����������ӵ�,�����ӵ������һ��������Ϸ��������ӵ�,��Ȼ�Կ�ƽ̨��ֱ����Ϊ��ĳ�������
	
	input:
		Ϊ�˷�ֹ�ԶԿ�ƽ̨ά����������ɸ��ģ����д���Ĳ�����Ϊconst����
		M, N : ���̴�С M - ���� N - ���� ����0��ʼ�ƣ� ���Ͻ�Ϊ����ԭ�㣬����x��ǣ�����y���
		_top : ��ǰ����ÿһ���ж���ʵ��λ��. e.g. ��i��Ϊ��,��_top[i] == M, ��i������,��_top[i] == 0
		_board : ���̵�һά�����ʾ, Ϊ�˷���ʹ�ã��ڸú����տ�ʼ���������Ѿ�����ת��Ϊ�˶�ά����board
				��ֻ��ֱ��ʹ��board���ɣ����Ͻ�Ϊ����ԭ�㣬�����[0][0]��ʼ��(����[1][1])
				board[x][y]��ʾ��x�С���y�еĵ�(��0��ʼ��)
				board[x][y] == 0/1/2 �ֱ��Ӧ(x,y)�� ������/���û�����/�г������,�������ӵ㴦��ֵҲΪ0
		lastX, lastY : �Է���һ�����ӵ�λ��, ����ܲ���Ҫ�ò�����Ҳ������Ҫ�Ĳ������ǶԷ�һ����
				����λ�ã���ʱ��������Լ��ĳ����м�¼�Է������ಽ������λ�ã�����ȫȡ�������Լ��Ĳ���
		noX, noY : �����ϵĲ������ӵ�(ע:��ʵ���������top�Ѿ����㴦���˲������ӵ㣬Ҳ����˵���ĳһ��
				������ӵ�����ǡ�ǲ������ӵ㣬��ôUI�����еĴ�����Ѿ������е�topֵ�ֽ�����һ�μ�һ������
				��������Ĵ�����Ҳ���Ը�����ʹ��noX��noY��������������ȫ��Ϊtop������ǵ�ǰÿ�еĶ�������,
				��Ȼ�������ʹ��lastX,lastY�������п��ܾ�Ҫͬʱ����noX��noY��)
		���ϲ���ʵ���ϰ����˵�ǰ״̬(M N _top _board)�Լ���ʷ��Ϣ(lastX lastY),��Ҫ���ľ�������Щ��Ϣ�¸������������ǵ����ӵ�
	output:
		������ӵ�Point
*/
class Board{
public:
	static const int maxDeep=8;
	//static const int pow4[]={1,4,16,64,256,1024,4096,16384,};
	int rows,lines;
	int noX,noY;
	int point[20][20];
	int top[20];
	int turn;// 1 means MAX turn, 0 means MIN turn
	int val;
	bool have4;
	//init
	Board(int size_m,int size_n,int **b,int t[],int now_turn,int no_x, int no_y){
		rows=size_m; //rows
		lines=size_n; //lines
		noX=no_x;
		noY=no_y;
		turn=now_turn;
		for(int i=0;i<rows;i++)
			for(int j=0;j<lines;j++)
				point[i][j]=b[i][j];
		for (int i=0;i<lines;i++)
			top[i]=t[i];
		//!!
		point[noX][noY]=4; //can not put
		val=0;//clear value
		have4=false;
	}
	
	bool canSet(int line){// n
		if (top[line]==0)
			return false;
		return true;
	}

	void set(int line){
		top[line]--;
		// now position point[top[line]][line] 
		point[top[line]][line]=1+turn;//1:My turn 2-1=2; 0: Program's turn, 2-0=1;
		//int eval=evaluate(top[line],line);
		if (line==noY && top[line]-1==noX)//can not put on this
			top[line]--;
		turn=1-turn;//next people's turn
		//return eval;
	}

	void unset(int line){
		if (line==noY && top[line]==noX)
			top[line]++;
		point[top[line]][line]=0;
		top[line]++;
		turn=1-turn;
	}
	
	int rcg(int *a)
	{
	int up=3;
	int weight=0;
	int same=0,blank=0,opp=0;
	for (int i=1;i<4;i++){
		if (a[i]+a[0]==3){// white/black, my point or opponent's point
			up=i-1;
			opp++;
			break;
		}
		if (a[i]==4)
		{
			up=i-1;
			break;
		}
		if (a[i]==a[0])  //same kind of point
			same++;
		else if(a[i]==0)
			blank++;

	}
	weight+=up*2;//bound
	weight+=same*4;//same
	weight+=blank*2;//blank
	//weight+= (opp-1)*3;
	return weight;
	}

	int targ(int length, int* a,int center,int depth)
	{
		int tt=0;
		bool fag=false;
		for (int i=center+1;i<length;i++)
			if (a[i]!=a[center])
			{
				tt+=i-center-1;
				fag=true;
				break;
			} 
		if (!fag)
			tt+=length-1-center;
		fag=false;
		for (int i=center-1;i>=0;i--)
			if (a[i]!=a[center])
			{
				tt+=center-i-1;
				fag=true;
				break;
			}
		if (!fag)
			tt+=center;
		//for (int i=0;i<length;i++)
			//_cprintf("%d",a[i]);
		//!!!debug
		tt+=1;
		//return tt;
		//_cprintf("center=%d,targ=%d\n",center,tt);
		if (tt>=4 )//&& abs(val)<500) //there is already a 4-point
		{
			have4=true;
			return 500;
		}
		else
			return 0;
	}
	int evaluate_line(int line,int depth)
	{
		point[top[line]-1][line]=1+turn;
		int temp=evaluate(top[line]-1,line,depth);
		point[top[line]-1][line]=0;
		return temp;
	}

	
	int evaluate(int x, int y,int depth)// row X  line Y
	{
		have4=false;
		int total=0,weight=0;
		int *a=new int[10];
		// horizon
		int length=0;
		int down,up;
		if (y>3)
			down=y-3;
		else
			down=0;
		if(y+3<lines)
			up=y+3;
		else
			up=lines-1;
		for (int i=0;i<4;i++)
			a[i]=4;// walls = 4 mine = 2 yours =1 nothing=0 can't put=4
		for (int i=y;i>=down;i--)
			a[y-i]=point[x][i];
		weight+=rcg(a);
		
		for (int i=0;i<4;i++)
			a[i]=4;// walls = 4 mine = 2 yours =1 nothing=0 can't put=4
		for (int i=y;i<=up;i++)
			a[i-y]=point[x][i];
		weight+=rcg(a);


		for (int i=0;i<9;i++)
			a[i]=4;// walls = 4 mine = 2 yours =1 nothing=0 can't put=4
		for (int i=down;i<=up;i++)
			a[i-down]=point[x][i];
		length=up-down+1;
		weight+=targ(length,a,y-down,depth);
		
		// verticle
		if (x>3)
			down=x-3;
		else
			down=0;
		if (x+3<rows)
			up=x+3;
		else
			up=rows-1;
		for (int i=0;i<4;i++)
			a[i]=4;
		for (int i=x;i>=down;i--)
			a[x-i]=point[i][y];
		weight+=rcg(a);

		for(int i=0;i<4;i++)
			a[i]=4;
		for(int i=x;i<=up;i++)
			a[i-x]=point[i][y];
		weight+=rcg(a);

		for(int i=0;i<9;i++)
			a[i]=4;
		for (int i=down;i<=up;i++)
			a[i-down]=point[i][y];
		length=up-down+1;
		weight+=targ(length,a,x-down,depth);


		//diagonal 
		int cx=x,cy=y;
		for(int i=0;i<4;i++){
			if (cx<0 || cy<0)
				a[i]=4;
			else
				a[i]=point[cx][cy];
			cx--;
			cy--;
		}
		weight+=rcg(a);

		int *b=new int[10];
		for(int i=0;i<4;i++)
		{
			b[i]=a[3-i];
		}
		cx=x;
		cy=y;
		for(int i=0;i<4;i++){
			if (cx>=rows || cy>=lines)
				a[i]=4;
			else
				a[i]=point[cx][cy];
			cx++;
			cy++;
		}
		weight+=rcg(a);

		for (int i=4;i<7;i++)
		{
			b[i]=a[i-3];
		}
		weight+=targ(7,b,3,depth);
		//counter- diagonal
		cx=x;cy=y;
		for(int i=0;i<4;i++){
			if (cx>=rows || cy<0)
				a[i]=4;
			else
				a[i]=point[cx][cy];
			cx++;
			cy--;
		}
		weight+=rcg(a);

		for(int i=0;i<4;i++)
		{
			b[i]=a[3-i];
		}
		cx=x;
		cy=y;
		for(int i=0;i<4;i++){
			if (cx<0 || cy>=lines)
				a[i]=4;
			else
				a[i]=point[cx][cy];
			cx--;
			cy++;
		}
		weight+=rcg(a);

		for (int i=4;i<7;i++)
		{
			b[i]=a[i-3];
		}
		weight+=targ(7,b,3,depth);
		//for (int i=0;i<7;i++)
			//_cprintf("%d,",b[i]);
		//_cprintf("(%d,%d)diag=%d\n",x,y,targ(7,b,3));
		
		//for debug
		/*_cprintf("up=%d,",up);
		for (int i=0;i<4;i++)
			_cprintf("%d,",a[i]);
		_cprintf("\n");*/
		delete []a;
		delete []b;
		return weight*(point[x][y]*2-3);		
	}

	struct Step{
		int line;
		int score;
		bool have4;
	};
	
	int path[20];
	int alphabeta(int alpha,int beta,int depth,int &pos){
		//_cprintf("(%d %d %d)\n", alpha,beta,depth);
		//print();
	   int choose=-1;
	   int score=0;
	   int available_lines=0;
	   Step step[20];
	   if (depth <= 0)  //Ҷ�ӽ�㣬�������ۺ���
	   {
			//_cprintf("value=%d\n",val);
			//print();
			//_cprintf("\n");
		    return val;//evaluate();
	   }
	   else if(turn == 1)  //  �����ߣ�MAX
	   {   
		  
			for(int i=0;i<lines;i++) // ÿ�������ߵ�λ�ã�
				if (canSet(i)){
					step[available_lines].line=i;
					step[available_lines].score=evaluate_line(i,depth);
					step[available_lines].have4=have4;
					available_lines++;
				}
			//sort by abs score
			for(int i=0;i<available_lines;i++)
				for(int j=i+1;j<available_lines;j++)
					if (abs(step[j].score)>abs(step[i].score))//swap
					{
						int k=step[j].score;
						step[j].score=step[i].score;
						step[i].score=k;
						k=step[j].line;
						step[j].line=step[i].line;
						step[i].line=k;
						bool b=step[j].have4;
						step[j].have4=step[i].have4;
						step[i].have4=b;
					}
			for(int i=0;i<available_lines;i++)
			{
				int eval=step[i].score;
				set(step[i].line);//set(i);//set i return evaluate
				val+=eval;
				//_cprintf("eval=%d,val=%d,posLine=%d\n",eval,val,i);
				if (step[i].have4)// this turn have a set four, no need to search after
				{				
					
					alpha=val;//score=-alphabeta(-beta,)...
					//_cprintf("value=%d HAVE4\n",val);
					//print();
					//_cprintf("\n");
					unset(step[i].line);
					val-=eval;
					if (depth==maxDeep)
					{
						pos=step[i].line;
					}
					return alpha;
				}
				else
					score= alphabeta(alpha,beta,depth-1,pos);
					//score =- alphabeta(-beta,-alpha,depth - 1,pos).score;
				//_cprintf("turn=%d,depth=%d,place=%d,score=%d,eval=%d\n",turn,depth,i,score,eval);
				unset(step[i].line); // �ָ�����״̬��
				val-=eval;
					 
					
					if(score > alpha){
						 alpha = score;
						 choose=step[i].line;
						 if(depth == maxDeep){   //����ǵ�һ�㣬���µ�ǰ�����λ��
							 pos = step[i].line;
						}
					}
					if(depth==maxDeep)
					{
						_cprintf("pos=%d,score=%d,value=%d,alpha=%d\n",step[i].line,score,step[i].score,alpha);
					}

					if(alpha >= beta) return alpha;//���м�֦

					
				}//if canSet
				return alpha;
		}
	   else
	   { //�Է��ߣ���Сֵ��� MIN
		   for(int i=0;i<lines;i++) // ÿ�������ߵ�λ�ã�
				if (canSet(i)){
					step[available_lines].line=i;
					step[available_lines].score=evaluate_line(i,depth);
					step[available_lines].have4=have4;
					available_lines++;
				}
			//sort by abs score
			for(int i=0;i<available_lines;i++)
				for(int j=i+1;j<available_lines;j++)
					if (abs(step[j].score)>abs(step[i].score))//swap
					{
						int k=step[j].score;
						step[j].score=step[i].score;
						step[i].score=k;
						k=step[j].line;
						step[j].line=step[i].line;
						step[i].line=k;
						bool b=step[j].have4;
						step[j].have4=step[i].have4;
						step[i].have4=b;
					}
			for(int i=0;i<available_lines;i++)
			{
				int eval=step[i].score;
				set(step[i].line);//set(i);//set i return evaluate
				val+=eval;
				//_cprintf("eval=%d,val=%d,posLine=%d\n",eval,val,i);
				if (step[i].have4)// this turn have a set four, no need to search after
				{				
					
					beta=val;//score=-alphabeta(-beta,)...
					//_cprintf("value=%d HAVE4\n",val);
					//print();
					//_cprintf("\n");
					unset(step[i].line);
					val-=eval;
					if (depth==maxDeep)
					{
						pos=step[i].line;
					}
					return beta;
				}
				else
					score= alphabeta(alpha,beta,depth-1,pos);
					//score =- alphabeta(-beta,-alpha,depth - 1,pos).score;
				//_cprintf("turn=%d,depth=%d,place=%d,score=%d,eval=%d\n",turn,depth,i,score,eval);
				unset(step[i].line); // �ָ�����״̬��
				val-=eval;
					 
					
					if(score < beta){
						 beta = score;
						 choose=step[i].line;
					}
					
					if(alpha >= beta) return beta;//���м�֦
					
				}//for available
				return beta;					
	   }
	}
	void print()
	{
	for (int i=0;i<rows;i++){
		for (int j=0;j<lines;j++)
			_cprintf("%d",point[i][j]);
		_cprintf("\n");
	}
	}
	int search()
	{
		int depth=maxDeep;
		int pos;
		alphabeta(MIN_INT,MAX_INT,depth,pos);
		return pos;
	}

};







extern "C" __declspec(dllexport) Point* getPoint(const int M, const int N, const int* _top, const int* _board, const int lastX, const int lastY, const int noX, const int noY){
	/*
		��Ҫ������δ���
	*/
	int x = -1, y = -1;//���ս�������ӵ�浽x,y��
	int* top = new int[N];
	for(int i = 0; i < N; i++){
		top[i] = _top[i];
	}
	int** board = new int*[M];
	for(int i = 0; i < M; i++){
		board[i] = new int[N];
		for(int j = 0; j < N; j++){
			board[i][j] = _board[i * N + j];
		}
	}
	
	/*
		�������Լ��Ĳ������������ӵ�,Ҳ���Ǹ�����Ĳ�����ɶ�x,y�ĸ�ֵ
		�ò��ֶԲ���ʹ��û�����ƣ�Ϊ�˷���ʵ�֣�����Զ����Լ��µ��ࡢ.h�ļ���.cpp�ļ�
	*/
	
	//Add your own code below
	
	AllocConsole();
	Board  newBoard(M,N,board,top,1,noX,noY);


	//newBoard.print();
	/*for (int i=0;i<N;i++)
	{
		_cprintf("evaluate=%d\n",newBoard.evaluate_line(i));
	}*/

	int next=newBoard.search();
	//x=top[0]-1;
	//y=0;
	x=top[next]-1;
	y=next;

	newBoard.print();
	_cprintf("(%d %d)\n", x,y);
	
	

	/*
		for(int i=0;i<N;i++){
		if(top[i]!=0){
			y = i;
			x = top[y]-1;
			break;
		}
	}
	*/


	/*
		��Ҫ������δ���
	*/
	clearArray(M, N, top, board);
	return new Point(x, y);
}


/*
	getPoint�������ص�Pointָ�����ڱ�dllģ���������ģ�Ϊ��������Ѵ���Ӧ���ⲿ���ñ�dll�е�
	�������ͷſռ䣬����Ӧ�����ⲿֱ��delete
*/
extern "C" __declspec(dllexport) void clearPoint(Point* p){
	delete p;
	return;
}

/*
	���top��board����
*/
void clearArray(int M, int N, int* top, int** board){
	delete[] top;
	for(int i = 0; i < M; i++){
		delete[] board[i];
	}
	delete[] board;
}


/*
	������Լ��ĸ�������������������Լ����ࡢ����������µ�.h .cpp�ļ�������ʵ������뷨
*/
