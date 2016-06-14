#ifndef ADC_H
#define ADC_H

#include "reg52.h"


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


unsigned char ADC_Process()
{
 unsigned char loop;
 unsigned char ADC_Dig0=0,ADC_Dig1=0;
 char tempbit;
 ADC_Dig0=0;
 ADC_Dig1=0;
 ADC_DI=1; //start signal
 ADC_CS=0; //enable adc
 //input choice( 10 for ch0;11 for ch1;00 for ch0+ch1-;01 for ch0-ch1+;)
 ADC_DownCLK();
 ADC_DI=1;
 ADC_DownCLK();
 ADC_DI=0;
 ADC_DownCLK();
 ADC_DownCLK();
 for (loop=0;loop<8;loop++)
 {
 	//dig0=dig0*2 + ADC_DO;	//×óÒÆÎ»£¿ dig<<=1	
	ADC_Dig0<<=1;
	tempbit=ADC_DO;
	ADC_Dig0=ADC_Dig0+tempbit;
	ADC_DownCLK();		
 }
 ADC_DownCLK();
  for (loop=0;loop<8;loop++)
 {
 	//dig1=dig1*2+ADC_DO;	//×óÒÆÎ»£¿ dig<<=1
	ADC_Dig1<<=1;
	tempbit=ADC_DO;
	ADC_Dig1=ADC_Dig1+tempbit;
	ADC_DownCLK();		
 }	
ADC_CS=1;//disable ADC
return ADC_Dig0;
}

#endif