#include<iostream>
#include<fstream>
//#define countlength 100;
using namespace std;
class Point
{
public:
	int x,y;
};

class Vec
{
public:
	int x,y;
	Vec()
	{
	x=0;
	y=0;
	}
};

Vec sub(Point a, Point b)
{
Vec c;
c.x=a.x-b.x;
c.y=a.y-b.y;
return c;
}

bool sameDir(Vec a, Vec b)
{
	if (a.x*b.x+a.y*b.y >= 0)
		return true;
	return false;
}

int  dist(Point a,Point b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

int main()
{
	ifstream fin;
	fin.open("d:/swing/out.txt");
	Point p[10000];
	int countlength=1000;
	double tx=0,ty=0;
	for (int i=0; i<countlength;i++)
	{
		int x,y;
		
		fin>>p[i].x>>p[i].y;
		//cout<<p[i].x<<" "<<p[i].y<<endl;

		tx+=p[i].x;
		ty+=p[i].y;
	}
	tx=tx/countlength;
	ty=ty/countlength;
	int avx=(int)tx;
	int avy=(int)ty;
	
	Point avp;
	avp.x=avx;
	avp.y=avy;



	//avp=p[2];
	cout<<avp.x<<" "<<avp.y<<endl;
	int prevd=0;
	bool dec=false;
	int changeDir=0;
	int startPoint=0;
	int numFreq=0;
	long countTime[1000];

	Vec prev;
	int minInter=5;
	int minDist=2;
	for (int i=1;i<countlength;i++)
	{
		if (dist(p[i],avp)<minDist && i-startPoint>minInter)
		{
			cout<<"half T:"<<i-startPoint<<endl;
			startPoint=i;
		}
	}



	/*
	for (int i=1;i<countlength;i++)
	{
		//int d=dist(p[i],avp);
		
		cout<<p[i].x<<" "<<p[i].y<<endl;
		Vec v;
		v=sub(p[i],p[i-1]);
		if (!sameDir(v,prev))
		{
			changeDir++;
			cout<<"changeDir"<<endl;
			if (changeDir==2)
			{
			changeDir=0;
			cout<<i-startPoint<<endl;
			startPoint=i;
			}
		}
		prev=v;
	}
	*/
	system("pause");
}