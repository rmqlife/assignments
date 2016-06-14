

//LCD1602define.h

#ifndef __LCD_H__
#define __LCD_H__

#define LCD_GO_HOME               0x02         //AC=0，光标、画面回HOME位

//输入方式设置
#define LCD_AC_AUTO_INCREMENT     0x06         //数据读、写操作后，AC自动增一
#define LCD_AC_AUTO_DECREASE      0x04         //数据读、写操作后，AC自动减一
#define LCD_MOVE_ENABLE           0x05         //数据读、写操作，画面平移
#define LCD_MOVE_DISENABLE        0x04         //数据读、写操作，画面不动

//设置显示、光标及闪烁开、关
#define LCD_DISPLAY_ON            0x0C         //显示开
#define LCD_DISPLAY_OFF           0x08         //显示关
#define LCD_CURSOR_ON             0x0A         //光标显示
#define LCD_CURSOR_OFF            0x08         //光标不显示
#define LCD_CURSOR_BLINK_ON       0x09         //光标闪烁
#define LCD_CURSOR_BLINK_OFF      0x08         //光标不闪烁

//光标、画面移动，不影响DDRAM
#define LCD_LEFT_MOVE             0x18         //LCD显示左移一位
#define LCD_RIGHT_MOVE            0x1C         //LCD显示右移一位
#define LCD_CURSOR_LEFT_MOVE      0x10         //光标左移一位
#define LCD_CURSOR_RIGHT_MOVE     0x14         //光标右移一位

//工作方式设置
#define LCD_DISPLAY_DOUBLE_LINE   0x38         //两行显示
#define LCD_DISPLAY_SINGLE_LINE   0x30         //单行显示

#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////

LCD1602.h
#ifndef __LCD_1602_CLIMBERWIN__
#define __LCD_1602_CLIMBERWIN__

#define uchar unsigned char
#define uint  unsigned int
#include <intrins.h>
#include"lcd1602define.h"
/******Port Definitions*****/
#define LCD_Data P0        //LCD的数据口
sbit LCD_BF=LCD_Data^7;    //LCD忙信号位
sbit LCD_RS = P1^5;
sbit LCD_RW = P1^6;
sbit LCD_EN = P1^7;

/*定义子程序*/
void LCD_ClrAll(void);              //清屏
void Judge_LCD_busy(void);           //检测是否忙碌
void LCD_Write(uchar WriteData);     //写控制字
void LCD_write_data(uchar LCD_data); //写数据显示
void LCD_cursor(uchar x);    //光标起始地址
void LCD_printc(unsigned char lcd_data) ;  //输出一个字符
void LCD_prints(unsigned char *lcd_string);//输出字符串

//void LCD_Back(void);

///*光标回到原点*/    //会出现警告？？？？
//void LCD_Back(void)
//{
 //LCD_Write(LCD_GO_HOME);
//}

//************************************************************************
/*LCD1602忙碌判断子程序*/
void Judge_LCD_busy(void)   //判断LCD1602是否忙状态
{
 while(1)
  {
   LCD_EN=0;
   LCD_RS=0;
   LCD_RW=1;
   LCD_Data=0xff;
   LCD_EN=1;   //EN 是 1—0 使能
   if(!LCD_BF)break; //LCD_BF=1表示忙碌，需要等待。
  }
   LCD_EN=0;
}
/******LCD清屏***************/
void LCD_ClrAll(void)
{

 Judge_LCD_busy();   //判断是否忙碌
 LCD_RS=0;
 LCD_RW=0;
 LCD_Data=0x01;
 LCD_EN=1;
 LCD_EN=0;

}
/*******LCD写数据定义各种模式*********/
void LCD_Write(uchar WriteData)   //写指令到LCD
{
 Judge_LCD_busy();
 LCD_RS=0;
 LCD_RW=0;

 LCD_Data=WriteData; //把WriteData的数据送到数据口
 LCD_EN=1;
 LCD_EN=0;
 }
/********LCD显示数据***********/
void LCD_write_data(uchar LCD_data)      //输出一个字节数据到LCD
{
 Judge_LCD_busy();
 LCD_RS=1;
 LCD_RW=0;

 LCD_Data=LCD_data;
 LCD_EN=1;
 LCD_EN=0;
 }


/****光标位置的确定***/
void LCD_cursor(uchar x)            //LCD光标定位到x处
{
 LCD_Write(0x80+x);                       //第一行地址是0x80

}


/*输出一个字符*/
void LCD_printc(unsigned char lcd_data)
{
 LCD_write_data(lcd_data);
}

/*输出字符串*/
void LCD_prints(unsigned char *lcd_string)
{
 unsigned char i=0;
 while(lcd_string[i]!=0x00)
  {
   LCD_write_data(lcd_string[i]);
   i++;
  }
}

/*初始化程序*/
void LCD_initial(void)                        //初始化LCD
{
 LCD_Write(LCD_AC_AUTO_INCREMENT|LCD_MOVE_DISENABLE);
 LCD_Write(LCD_DISPLAY_ON|LCD_CURSOR_OFF);
 LCD_Write(LCD_DISPLAY_DOUBLE_LINE);
 LCD_ClrAll();
}


#endif
