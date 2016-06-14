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


unsigned char UART_Get()
{
unsigned char recv;
	
	recv=SBUF;
	RI=0;
	return recv;
}