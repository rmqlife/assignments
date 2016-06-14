#include "reg52.h"
#include "lcd1602.h"
#include "adc.h"



void main()
{
 ADC_Init();
 LCD_Init();
 LCD_Write_String(0,0,"ADC0832:");
 while (1)
 {
 int loop;
 float adcout;
 unsigned char dig0=ADC_Process();
 adcout=(float) dig0/128*5;
 for (loop=intlength(dig0);loop<7;loop++)
 	LCD_Write_Char(loop,1,' ');
//LCD_Write_Float(8,1,adcout,3);
 LCD_Write_Float(8,0,adcout,3);
 //LCD_Write_int(8,1,dig1);
 ADC_Delay(5000);
 }
}