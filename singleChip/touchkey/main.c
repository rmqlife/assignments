#include"lcd1602.h"
sbit key=P1^1;
void main()
{
LCD_Init();
while(1)
	{
	LCD_Write_String(0,0,"Touchpad");
	if (key)
		LCD_Write_Char(0,1,'1');
	else
		LCD_Write_Char(0,1,'0');
	}
}