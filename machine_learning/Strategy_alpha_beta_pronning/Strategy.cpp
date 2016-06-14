#include <iostream>
#include "Point.h"
#include "Strategy.h"
#include <conio.h>
#include <atlstr.h>

#define MIN_INT -100000
#define MAX_INT 100000
using namespace std;

/*
	策略函数接口,该函数被对抗平台调用,每次传入当前状态,要求输出你的落子点,该落子点必须是一个符合游戏规则的落子点,不然对抗平台会直接认为你的程序有误
	
	input:
		为了防止对对抗平台维护的数据造成更改，所有传入的参数均为const属性
		M, N : 棋盘大小 M - 行数 N - 列数 均从0开始计， 左上角为坐标原点，行用x标记，列用y标记
		_top : 当前棋盘每一列列顶的实际位置. e.g. 第i列为空,则_top[i] == M, 第i列已满,则_top[i] == 0
		_board : 棋盘的一维数组表示, 为了方便使用，在该函数刚开始处，我们已经将其转化为了二维数组board
				你只需直接使用board即可，左上角为坐标原点，数组从[0][0]开始计(不是[1][1])
				board[x][y]表示第x行、第y列的点(从0开始计)
				board[x][y] == 0/1/2 分别对应(x,y)处 无落子/有用户的子/有程序的子,不可落子点处的值也为0
		lastX, lastY : 对方上一次落子的位置, 你可能不需要该参数，也可能需要的不仅仅是对方一步的
				落子位置，这时你可以在自己的程序中记录对方连续多步的落子位置，这完全取决于你自己的策略
		noX, noY : 棋盘上的不可落子点(注:其实这里给出的top已经替你处理了不可落子点，也就是说如果某一步
				所落的子的上面恰是不可落子点，那么UI工程中的代码就已经将该列的top值又进行了一次减一操作，
				所以在你的代码中也可以根本不使用noX和noY这两个参数，完全认为top数组就是当前每列的顶部即可,
				当然如果你想使用lastX,lastY参数，有可能就要同时考虑noX和noY了)
		以上参数实际上包含了当前状态(M N _top _board)以及历史信息(lastX lastY),你要做的就是在这些信息下给出尽可能明智的落子点
	output:
		你的落子点Point
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
	   if (depth <= 0)  //叶子结点，返回评价函数
	   {
			//_cprintf("value=%d\n",val);
			//print();
			//_cprintf("\n");
		    return val;//evaluate();
	   }
	   else if(turn == 1)  //  本方走，MAX
	   {   
		  
			for(int i=0;i<lines;i++) // 每个可以走的位置；
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
				unset(step[i].line); // 恢复棋盘状态；
				val-=eval;
					 
					
					if(score > alpha){
						 alpha = score;
						 choose=step[i].line;
						 if(depth == maxDeep){   //如果是第一层，更新当前走棋的位置
							 pos = step[i].line;
						}
					}
					if(depth==maxDeep)
					{
						_cprintf("pos=%d,score=%d,value=%d,alpha=%d\n",step[i].line,score,step[i].score,alpha);
					}

					if(alpha >= beta) return alpha;//进行剪枝

					
				}//if canSet
				return alpha;
		}
	   else
	   { //对方走，最小值情况 MIN
		   for(int i=0;i<lines;i++) // 每个可以走的位置；
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
				unset(step[i].line); // 恢复棋盘状态；
				val-=eval;
					 
					
					if(score < beta){
						 beta = score;
						 choose=step[i].line;
					}
					
					if(alpha >= beta) return beta;//进行剪枝
					
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
		不要更改这段代码
	*/
	int x = -1, y = -1;//最终将你的落子点存到x,y中
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
		根据你自己的策略来返回落子点,也就是根据你的策略完成对x,y的赋值
		该部分对参数使用没有限制，为了方便实现，你可以定义自己新的类、.h文件、.cpp文件
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
		不要更改这段代码
	*/
	clearArray(M, N, top, board);
	return new Point(x, y);
}


/*
	getPoint函数返回的Point指针是在本dll模块中声明的，为避免产生堆错误，应在外部调用本dll中的
	函数来释放空间，而不应该在外部直接delete
*/
extern "C" __declspec(dllexport) void clearPoint(Point* p){
	delete p;
	return;
}

/*
	清除top和board数组
*/
void clearArray(int M, int N, int* top, int** board){
	delete[] top;
	for(int i = 0; i < M; i++){
		delete[] board[i];
	}
	delete[] board;
}


/*
	添加你自己的辅助函数，你可以声明自己的类、函数，添加新的.h .cpp文件来辅助实现你的想法
*/
