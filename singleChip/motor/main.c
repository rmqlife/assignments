#include"lcd1602.h"
#include"remote.h"
#define motor P1

unsigned char DeltaT;
void ACWise()
{
DelayMs(DeltaT);
motor=0x03;
DelayMs(DeltaT);
motor=0x06;
DelayMs(DeltaT);
motor=0x0c;
DelayMs(DeltaT);
motor=0x09;
}
void CWise()
{
DelayMs(DeltaT);
motor=0x09;
DelayMs(DeltaT);
motor=0x0c;
DelayMs(DeltaT);
motor=0x06;
DelayMs(DeltaT);
motor=0x03;
}



void main()
{
bit CWfag=1;
motor=0x00;
LCD_Init();
LCD_Write_String(0,0,"Motor!");
Remote_Init();
DeltaT=10;
while(1)
	{

	
	if (CWfag)
		{CWise();}
	else {ACWise();}
	if (Remote_FAG)
	{
	char k=Remote_Key();
		switch (k)
		{
		case 'U': DeltaT+=10; break;
		case 'D': if (DeltaT>11) DeltaT-=10; break;
		case '+': DeltaT+=1; break;
		case '-': if (DeltaT>2) DeltaT-=1; break;
		case 'r': CWfag=!CWfag; 
		};
	LCD_Write_String(5,1,"   ");
	LCD_Write_Int(5,1,DeltaT);
	LCD_Write_Char(8,1,k);
	Remote_FAG=0;
	} 

	
	}			//while
}