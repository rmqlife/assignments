#include "reg52.h"
#include "lcd1602.h"


sbit ADC_CS=P1^1;  //enable chip
sbit ADC_DI=P1^2;  //digital in:choose chanel
sbit ADC_DO=P1^3; //digital out
sbit ADC_CLK=P1^4;

void ADC_Delay(unsigned int timer)								
{
	while(timer--);
}

void ADC_Init()
{
	ADC_CS=1;//unable adc
	ADC_CLK=1;
}

void ADC_DownCLK()
{
 ADC_Delay(10);
 ADC_CLK=0;
 ADC_Delay(10);
 ADC_CLK=1;
 ADC_Delay(10);	 
}

unsigned char dig0=0,dig1=0;
void ADC_Process()
{
 unsigned char i;
 char tempbit;
 dig0=0;
 dig1=0;
 ADC_DI=1; //start signal
 ADC_CS=0; //enable adc
 //input choice( 10 for ch0;11 for ch1;00 for ch0+ch1-;01 for ch0-ch1+;)
 ADC_DownCLk();
 ADC_DI=1;
 ADC_DownCLk();
 ADC_DI=0;
 ADC_DownCLk();
 ADC_DownCLk();
 for (i=0;i<8;i++)
 {
 	//dig0=dig0*2 + ADC_DO;	//×óÒÆÎ»£¿ dig<<=1	
	dig0<<=1;
	tempbit=ADC_DO;
	dig0=dig0+tempbit;
	ADC_DownCLk();		
 }
 ADC_DownCLk();
  for (i=0;i<8;i++)
 {
 	//dig1=dig1*2+ADC_DO;	//×óÒÆÎ»£¿ dig<<=1
	dig1<<=1;
	tempbit=ADC_DO;
	dig1=dig1+tempbit;
	ADC_DownCLk();		
 }	
ADC_CS=1;//disable ADC
}




void main()
{
 ADC_Init();
 LCD_Init();
 LCD_Write_String(0,0,"ADC0832:");
 while (1)
 {
 int loop;
 float adcout;
 ADC_Process();
 adcout=(float)dig0/128*5;
 for (loop=intlength(dig0);loop<7;loop++)
 	LCD_Write_Char(loop,1,' ');
//LCD_Write_Float(8,1,adcout,3);
 LCD_Write_Float(8,0,adcout,3);
 
 //LCD_Write_int(8,1,dig1);
 ADC_Delay(5000);
 }
}