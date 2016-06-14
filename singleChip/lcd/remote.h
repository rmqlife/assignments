#ifndef REMOTE_H
#define REMOTE_H

#include "reg52.h"


unsigned char Remote_CY[4];						//NEC为四个字节数据
bit Remote_FAG;								//成功接收标志
sbit Remote_PIN=P3^3;		//定义红外接收脚，outside interrupt			
const char Remote_Table[30]={'p','x','m','x','+','U','r','x','L','K','R','x','-','D','0','x','1','2','3','x','4','5','6','x','7','8','9'};
//						      00  01  02  03  04  05  06  07  08  09  0a  0b  0c  0d  0e  0f  10  11  12  13  14  15  16  17  18  19  1a
/*
char loop;
void main()
{
LCD_Init();
LCD_Write_String(0,0,"Remote");
Remote_Init();
while (1)
	{
	//char k=waitkey();	
	//LCD_Write_Char(6,0,k);				
	//DelayMs(3000);
	if (Remote_FAG)
		{
			Remote_FAG=0;
			
	//LCD_Write_String(8,0,"Signal");		
	for (loop=0;loop<4;loop++)
		LCD_Write_HEX(3*loop,1,Remote_CY[loop]);
	
	LCD_Write_HEX(8,0,Remote_CY[3]+Remote_CY[2]);		
		}
	}
}
*/


void Remote_Init()
{
	EA=1;					//首先开启总中断
	EX1=1;  				//开启外部中断 1
	IT1=1;        			//设置成下降沿触发方式
	TMOD=0X10;				//定时器1的方式1，16位计数器，用来计数时间
	Remote_FAG=0;
}


/*************延时子函数 ********************************************************/
void Remote_Delay(unsigned char timer)								
{
	while(timer--);
}

/***********外中断1入口函数，P33引脚，红外线接收IC数据脚**************************/
void Remote_Check(void)   interrupt 2
{
	unsigned char i,ia;
	/**************开始判断是否为NEC波形引导码的前9MS******************************/
	TL1=0;
	TH1=0;				//定时/计数器1初始值
	TR1=1;				//定时器以12M晶振12分频计数，即1us计数
	while(!Remote_PIN){		//引脚低电平时的处理	
		Remote_Delay(10);		//廷时，避免频繁读取计数器值的作用，可不用。
		if(TH1>40)		//这是为了信号错误码而设,即大于40的计数值就要退出,因为NEC引导码最大为9MS，计数约9000，TH1约等于35
			return;		
	}
	TR1=0;				//信号翻转停止计数
	if(TH1<30)			//还要判断小于30为非NEC制编码退出,否则继续接收数据
		return;

	TH1=0;				//定时/计数器1初始值
	TR1=1;
	while(Remote_PIN){			//引导码的后4。5MS高电平时等待
		Remote_Delay(10);
		if(TH1>25)		//4。5MS，约等于17
			return;		
	}

	/***********开始接收四个字节内容**************************************/	
	for(i=0;i<4;i++){
		for(ia=0;ia<8;ia++){
			//低电平开始，不处理只等待高电平，这里是为了判断错误信号时退出
			TH1=0;					//定时计数器1初始值
			TR1=1;					//启动计数
			while(!Remote_PIN){			//接收低电平时间量
				Remote_Delay(10);
				if(TH1>15)
					return;			//错误信号退出
			}
			//低电平结束			
			//高电平开始，
			TH1=0;
			while(Remote_PIN){
				Remote_Delay(10);
				if(TH1>15)		
					return;		
			}
			TR1=0;
			//高电平结束，判断数据1或0向变量移入
			Remote_CY[i]>>=1;			//数据由高位移入低位
			if(TH1>4)				//时间量TH1高于4，即高于1MS判断为1
				Remote_CY[i]|=0x80;
		}
	}
	if(Remote_CY[2]+Remote_CY[3]==0xff)
		Remote_FAG=1;	//接收成功
	TF1=0;
}


char Remote_Key()
{
	return Remote_Table[Remote_CY[2]];
}
#endif