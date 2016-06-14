#ifndef LCD1602_H
#define LCD1602_H
/*-----------------------------------------------
  名称：LCD1602
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：通过标准程序静态显示字符
  引脚定义如下：1-VSS 2-VDD 3-V0 4-RS 5-R/W 6-E 7-14 DB0-DB7 15-BLA 16-BLK
------------------------------------------------*/
#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<intrins.h>

sbit RS = P0^7;   //定义端口 
sbit RW = P0^6;
sbit EN = P0^5;

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

#define DataPort P2

/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/

void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
/*------------------------------------------------
              判忙函数
------------------------------------------------*/
 bit LCD_Check_Busy(void) 
 { 
 DataPort= 0xFF; 
 RS_CLR; 
 RW_SET; 
 EN_CLR; 
 _nop_(); 
 EN_SET;
 return (bit)(DataPort & 0x80);
 }
/*------------------------------------------------
              写入命令函数
------------------------------------------------*/
 void LCD_Write_Com(unsigned char com) 
 {  
 while(LCD_Check_Busy()); //忙则等待
 RS_CLR; 
 RW_CLR; 
 EN_SET; 
 DataPort= com; 
 _nop_(); 
 EN_CLR;
 }
/*------------------------------------------------
              写入数据函数
------------------------------------------------*/
 void LCD_Write_Data(unsigned char Data) 
 { 
 while(LCD_Check_Busy()); //忙则等待
 RS_SET; 
 RW_CLR; 
 EN_SET; 
 DataPort= Data; 
 _nop_();
 EN_CLR;
 }

/*------------------------------------------------
                清屏函数
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 DelayMs(5);
 }
/*------------------------------------------------
              写入字符串函数
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 {     
 if (y == 0) 
 	{     
	 LCD_Write_Com(0x80 + x);     //表示第一行
 	}
 else 
 	{      
 	LCD_Write_Com(0xC0 + x);      //表示第二行
 	}        
 while (*s) 
 	{     
 LCD_Write_Data( *s);     
 s ++;     
 	}
 }
/*------------------------------------------------
              写入字符函数
------------------------------------------------*/
 void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
 {     
 if (y == 0) 
 	{     
 	LCD_Write_Com(0x80 + x);     
 	}    
 else 
 	{     
 	LCD_Write_Com(0xC0 + x);     
 	}        
 LCD_Write_Data(Data);  
 }
/*------------------------------------------------
              初始化函数
------------------------------------------------*/
 void LCD_Init(void) 
 {
   LCD_Write_Com(0x38);    /*显示模式设置*/ 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*显示关闭*/ 
   LCD_Write_Com(0x01);    /*显示清屏*/ 
   LCD_Write_Com(0x06);    /*显示光标移动设置*/ 
   DelayMs(5); 
   LCD_Write_Com(0x0C);    /*显示开及光标设置*/
   }
 
 char row=0,line=0;
 void LCD_Write_Char2(unsigned char k)
 {
  LCD_Write_Char(row,line,k);
  row++;
  line=(line+row/16)%2;
  row=row%16;
 
 } 
 
 



void LCD_Write_HEX(unsigned char x,unsigned char y,unsigned char Data)
{
char hex[2];
char loop;
hex[1]=Data%16;
hex[0]=Data/16;
for (loop=0;loop<2;loop++)	
	{
	if (hex[loop]<10)
		{hex[loop]=hex[loop]+48;}
	 else {hex[loop]=hex[loop]+87;}
	LCD_Write_Char(x+loop,y,hex[loop]);
	}
}


void LCD_Write_Int(unsigned char x,unsigned char y,unsigned long Data)
{
unsigned char x0=x,y0=y,loop,numlength=0;
unsigned char outnum[10];
do
{
	outnum[numlength]=Data % 10 + 48;
	Data=Data/10;
	numlength++;
} while (Data>0);
for (loop=0;loop<numlength;loop++)
	LCD_Write_Char(x0+loop,y0,outnum[numlength-loop-1]);
}

unsigned char intlength(unsigned long Data)
{
unsigned char length;
do
{
Data=Data/10;
length++;
}
while (Data>0);
return length;
}




void LCD_Write_Float(unsigned char x,unsigned char y,float Data,unsigned char dot)
//dot 为保留的小数点位数。
{
unsigned long templong=1;
unsigned char loop,templength,tempchar;
templong=(long)Data; //=floor 下取整
LCD_Write_Int(x,y,templong);
templength=intlength(templong);
LCD_Write_Char(x+templength,y,'.');
Data=Data-templong;
for (loop=0;loop<dot;loop++)
{
	Data=Data*10;
	tempchar=(char)Data;
	LCD_Write_Char(x+templength+1+loop,y,tempchar+48);	
	Data=Data-tempchar;
}
}
#endif