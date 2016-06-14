#include"lcd1602.h"
#include"ds18b20.h"
float Temp_Digi()
{
unsigned char *tempp;
unsigned char temp_LS,temp_MS;
float temp=1;
tempp=ReadTemperature(TEMPHIGH,TEMPLOW,0x3f);
temp_LS=*tempp;
temp_MS=*(tempp+1);
temp=temp_LS/16+(temp_MS&0x07)*16+(float)(temp_LS%16)/16 ;
return temp;
}



void main()
{
char loop;
LCD_Init();
LCD_Write_String(0,0,"temp:");
while (1)
	{	
		float t=Temp_Digi();
		LCD_Write_Float(5,0,t,2);
		LCD_Write_String(5+intlength(t)+1,0,"C  ");
		DelayMs(255);		
	}
}