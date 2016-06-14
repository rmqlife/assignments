#include"lcd1602.h"

sbit light=P1^7;

void main()
{
LCD_Init();
LCD_Write_String(0,0,"Light counter");
light=0;
while(1)
{
if (light)
	LCD_Write_Char(0,1,'1');
else 
	LCD_Write_Char(0,1,'0');			
}


}