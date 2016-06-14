#include "lcd1602.h"
//#include "key.h"
//#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "sonar.h"
#include "remote.h"
#include "reg52.h"
sbit Sound=P1^0;
sbit Check=P2^0;

/*void Sound_Endure() interrupt 1
{
TL0=63341%256;
TH0=63341/256;
Sound=!Sound;
}

void Sound_Init()
{
EA=1;
TL0=63341%256;
TH0=63341/256;
ET0=1;
TR0=1;
TMOD=1;
}*/

unsigned int mem;
void main()
{
LCD_Init();
Remote_Init();
//LCD_Light=1;
LCD_Write_String(0,0,"Sound");
//Sound_Init();
while (1)
	{
	//char k=waitkey();	
	//LCD_Write_Char(6,0,k);				
	//DelayMs(3000);
	if (Remote_FAG)
		{
			Remote_FAG=0;
			LCD_Write_Char(7,0,Remote_Key());			
		}
	/*if (Check)
		TR1=1;
	if (!Check)
		{
		TR1=0;
		TL1=0;
		TH1=0;
		mem=TL1+TH1*256;
		}
	if (Remote_FAG)
		{
			Remote_FAG=0;
			LCD_Write_Char(7,0,Remote_Key());			
			if (Remote_Key()=='K')
			{
				char * memstring;
				itoa(mem,memstring);
				LCD_Write_String(0,1,memstring);			
			}
		}
	*/
	}
}