#include"lcd1602.h"

void UART_Init()
{
	SCON=0x50;//8 bit data
	T2CON=0x34;//T/C2
	//RCAP2L=0xd9;
	//RCAP2H=0xff;//baud:9600bit/s 12MHz L 12M/(2*16*(65536-t))
	RCAP2L=0xdc;
	RCAP2H=0xff; //t=11.0592M/(2*16*baud9600)
	ES=1;//enable serial interrupt
	EA=1;//enable all interrupt
}

void UART_SendByte(unsigned char byte)
{
	SBUF=byte;
	while (TI==0);//·¢ËÍfinished TI=1;
	TI=0;//clear
}

/*void UART_IRQ() interrupt 4 //using interrupt
{
	unsigned char recv;
	if (RI)
	{		
		recv=SBUF;
		UART_SendByte(recv);
		LCD_Write_HEX(0,1,recv);
		RI=0;	
	}
}*/


unsigned char UART_Get()
{
unsigned char recv;
		
		recv=SBUF;
		RI=0;
		return recv;
}




unsigned char lcdx=0;
void main()
{

UART_Init();
LCD_Init();
LCD_Write_String(0,0,"btSerial:R&S");
LCD_Show_Cursor();
while (1)
{
unsigned char recv;
if (RI)
	{
	recv=UART_Get();
	UART_SendByte(recv);
	LCD_Write_Char(lcdx,1,recv);
	lcdx=(lcdx+1)%16;	
	}	
}//while

}