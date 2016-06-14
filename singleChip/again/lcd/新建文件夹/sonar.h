#include<reg52.h>
sbit ECHO=P1^0;//ECHO
sbit TRIG=P1^1;//TRIG

unsigned long sl=0,length=0;
char loop;
char slstring[8]="";
unsigned char l_disbuff[4]	   ={ 0,0,0,0,};//œ‘ æª∫≥Â
unsigned char counter;
unsigned long result;
void timer_us() interrupt 1
{	
	counter++;	
}


unsigned long Sonar_Count()
{	
while (ECHO==0) {};
TR0=1;
EA=1;
ET0=1;
counter=0;
while (ECHO &&counter<10) {};
EA=0;
ET0=0;
TR0=0;
result=counter*65536+TH0*256+TL0;
return result;
}



void Sonar_Init()
{
	TRIG=0;
	TR0=0;
	ECHO=0;
	TMOD=1;
	TL0=0;
	TH0=0;	
}



void Sonar_Start()
{
	TRIG=0;
	DelayMs(1);
	TRIG=1;
	DelayMs(1);
	TRIG=0;
	counter=0;		
}


int Sonar()
{
 	Sonar_Init(); 	
	Sonar_Start();
	return Sonar_Count();
}