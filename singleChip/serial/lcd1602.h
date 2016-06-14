#ifndef LCD1602_H
#define LCD1602_H
/*-----------------------------------------------
  ���ƣ�LCD1602
  ��̳��www.doflye.net
  ��д��shifang
  ���ڣ�2009.5
  �޸ģ���
  ���ݣ�ͨ����׼����̬��ʾ�ַ�
  ���Ŷ������£�1-VSS 2-VDD 3-V0 4-RS 5-R/W 6-E 7-14 DB0-DB7 15-BLA 16-BLK
------------------------------------------------*/
#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include<intrins.h>

sbit RS = P0^7;   //����˿� 
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
 uS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
 �������� T=tx2+5 uS 
------------------------------------------------*/

void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //������ʱ1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
/*------------------------------------------------
              ��æ����
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
              д�������
------------------------------------------------*/
 void LCD_Write_Com(unsigned char com) 
 {  
 while(LCD_Check_Busy()); //æ��ȴ�
 RS_CLR; 
 RW_CLR; 
 EN_SET; 
 DataPort= com; 
 _nop_(); 
 EN_CLR;
 }
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
 void LCD_Write_Data(unsigned char Data) 
 { 
 while(LCD_Check_Busy()); //æ��ȴ�
 RS_SET; 
 RW_CLR; 
 EN_SET; 
 DataPort= Data; 
 _nop_();
 EN_CLR;
 }

/*------------------------------------------------
                ��������
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 DelayMs(5);
 }
/*------------------------------------------------
              д���ַ�������
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 {     
 if (y == 0) 
 	{     
	 LCD_Write_Com(0x80 + x);     //��ʾ��һ��
 	}
 else 
 	{      
 	LCD_Write_Com(0xC0 + x);      //��ʾ�ڶ���
 	}        
 while (*s) 
 	{     
 LCD_Write_Data( *s);     
 s ++;     
 	}
 }
/*------------------------------------------------
              д���ַ�����
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
              ��ʼ������
------------------------------------------------*/
 void LCD_Init(void) 
 {
   LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*��ʾ�ر�*/ 
   LCD_Write_Com(0x01);    /*��ʾ����*/ 
   LCD_Write_Com(0x06);    /*��ʾ����ƶ�����*/ 
   DelayMs(5); 
   LCD_Write_Com(0x0C);    /*��ʾ�����������*/
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
//dot Ϊ������С����λ����
{
unsigned long templong=1;
unsigned char loop,templength,tempchar;
templong=(long)Data; //=floor ��ȡ��
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