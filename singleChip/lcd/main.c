#include"lcd1602.h"
#include"remote.h"

//relay 继电器模块，remote 接p33,两路分别接p10p11, 按1、2键打开两路开关，起始关断。
sbit Relay_S1=P1^0;
sbit Relay_S2=P1^1;

void main()
{
LCD_Init();
LCD_Write_String(0,0,"Relay");
Remote_Init();
Relay_S1=1;
Relay_S2=1;
while(1)
{
char k;
if (Remote_FAG)
{
	k=Remote_Key();
	LCD_Write_Char(12,0,k);
	if (Remote_Key()=='1')
		Relay_S1=!Relay_S1;
	if (Remote_Key()=='2')
		Relay_S2=!Relay_S2;	
	Remote_FAG=0;
}

}
}