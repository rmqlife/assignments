#include "lcd1602.h"
#include "key.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sonar.h"




unsigned long sl=0,length=0;
char loop;
char slstring[8]="";
unsigned char l_disbuff[4]	   ={ 0,0,0,0,};//显示缓冲


void main()
{
LCD_Init();
LCD_Write_String(0,0,"Sonar");

while (1)
	{
	char k=waitkey();	
	LCD_Write_Char(6,0,k);
	
	if (k=='A')
		{
		
		sl=Sonar();
		length=(sl*0.18446)/10;
		l_disbuff[0]=length%1000/100+0x30;		//这里加上0X30是将数字转为ASCII码
	  	l_disbuff[1]=length%1000%100/10+0x30;
	  	l_disbuff[2]=length%1000%10%10+0x30;
	  	LCD_Write_Char(0, 1,l_disbuff[0]);
	  	LCD_Write_Char(1, 1,'.');			//显示点
	  	LCD_Write_Char(2, 1,l_disbuff[1]);
	  	LCD_Write_Char(3, 1,l_disbuff[2]);
	  	LCD_Write_Char(4, 1,'M');	
		//sl=(int)sl*340/1000/2;	
		itoa(sl,slstring);
		//strcat(slstring,"cm");
		LCD_Write_String(9,0,slstring);
		}
				
	DelayMs(3000);
	}
}