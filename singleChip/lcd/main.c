#include"lcd1602.h"
#include"remote.h"

//relay �̵���ģ�飬remote ��p33,��·�ֱ��p10p11, ��1��2������·���أ���ʼ�ضϡ�
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