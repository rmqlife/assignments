#include "lcd1602.h"
#include "key.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "sonar.h"
//#include "remote.h"
#include "reg52.h"
sbit Sound=P1^0;
//sbit Check=P2^0;
sbit Listen=P1^3;


unsigned int numa=440;
unsigned long freq;
void Sound_Endure() interrupt 1
{
TL0=freq%256;
TH0=freq/256;
Sound=!Sound;
}


bit last,now;
unsigned int L_length,L_n=0;
unsigned long L_avlength=0,L_freq;

void Listen_Init()
{
L_n=0;
L_avlength=0;
TL1=0;
TH1=0;
TR1=1;
}




int Listen_Endure()
{
Listen_Init();
while(1)
{
	now=Listen;
	if (now && !last)//ÉÏÉýÑØ
		{
		L_length=TH1*256+TL1;
		L_avlength=(L_avlength*L_n+L_length)/(L_n+1);
		TL1=0;
		TH1=0;
		L_n++;
		}
	if (L_n>100)
		{
		L_freq=921600/L_avlength;
		L_n=0;
		L_avlength=0;		
		//LCD_Write_Int(0,1,numa);
		break;	
		}	
	last=now;
}
return (int)L_freq;
}




void Sound_Init()
{
EA=1;
TL0=0;//63341%256;
TH0=0;//63341/256;
ET0=1;
TR0=1;
TMOD=1;
}

unsigned int mem;
char * memstring;
void main()
{
LCD_Init();
//Remote_Init();
//LCD_Light=1;
LCD_Write_String(0,0,"Sound");
LCD_Write_Int(0,1,numa);
Sound_Init();
freq=(65536-921600/numa);

LCD_Write_String(LCD_Write_Int(0,1,numa),1,"Hz");	
while (1)
	{
	
	char k=waitkey();
		
	LCD_Write_Char(6,0,k);					
	
	switch (k)
	{
	case 'A':if (1)numa+=100;break;
	case 'B':if (1)numa-=100;break;
	case 'C':if (1)numa+=10;break;
	case 'D':if (1)numa-=10;break;
	}
	freq=(65536-921600/numa);
	k=LCD_Write_Int(0,1,numa);
	LCD_Write_String(k,1,"Hz");	
	DelayMs(3000);
	
	
	
	/*char k=waitkey();
	if (k=='1')
	{	 
	char * memstring;
	itoa(mem,memstring);
	LCD_Write_String(0,1,memstring);
	}
	if (Remote_FAG)
		{
			Remote_FAG=0;
			LCD_Write_Char(7,0,Remote_Key());			
		}
	*/

	}
}