#include"lcd1602.h"

#include"uart.h"

unsigned char Mind_DATA[50];
char Mind_COUNT;


bit Mind_Init()
{
UART_SendByte(0x00);
Mind_COUNT=0;
return 1;
}


void Mind_Process()
{
unsigned char recv,prev=0x00;;
while(1)
	{
	if (RI)
		{
		recv=UART_Get();
		Mind_DATA[Mind_COUNT]=recv;
		Mind_COUNT++;
		if (recv==0xaa && prev==0xaa)
			{
			Mind_COUNT=0;
			break;
			}
		prev=recv;	
		}	
	}
}




void main()
{

UART_Init();
LCD_Init();
LCD_Write_String(0,0,"MindReader_2");
LCD_Show_Cursor();
Mind_Init();
while(1)
{
	Mind_Process();
	LCD_Write_HEX(0,1,Mind_DATA[1]);
	LCD_Write_HEX(2,1,Mind_DATA[2]);//poor of mind after 02
	
	LCD_Write_HEX(5,1,Mind_DATA[29]);
	LCD_Write_HEX(7,1,Mind_DATA[30]);  //after	04
	
	LCD_Write_HEX(10,1,Mind_DATA[31]);  //after  05
	LCD_Write_HEX(12,1,Mind_DATA[32]);
}

}