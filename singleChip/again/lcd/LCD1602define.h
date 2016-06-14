

//LCD1602define.h

#ifndef __LCD_H__
#define __LCD_H__

#define LCD_GO_HOME               0x02         //AC=0����ꡢ�����HOMEλ

//���뷽ʽ����
#define LCD_AC_AUTO_INCREMENT     0x06         //���ݶ���д������AC�Զ���һ
#define LCD_AC_AUTO_DECREASE      0x04         //���ݶ���д������AC�Զ���һ
#define LCD_MOVE_ENABLE           0x05         //���ݶ���д����������ƽ��
#define LCD_MOVE_DISENABLE        0x04         //���ݶ���д���������治��

//������ʾ����꼰��˸������
#define LCD_DISPLAY_ON            0x0C         //��ʾ��
#define LCD_DISPLAY_OFF           0x08         //��ʾ��
#define LCD_CURSOR_ON             0x0A         //�����ʾ
#define LCD_CURSOR_OFF            0x08         //��겻��ʾ
#define LCD_CURSOR_BLINK_ON       0x09         //�����˸
#define LCD_CURSOR_BLINK_OFF      0x08         //��겻��˸

//��ꡢ�����ƶ�����Ӱ��DDRAM
#define LCD_LEFT_MOVE             0x18         //LCD��ʾ����һλ
#define LCD_RIGHT_MOVE            0x1C         //LCD��ʾ����һλ
#define LCD_CURSOR_LEFT_MOVE      0x10         //�������һλ
#define LCD_CURSOR_RIGHT_MOVE     0x14         //�������һλ

//������ʽ����
#define LCD_DISPLAY_DOUBLE_LINE   0x38         //������ʾ
#define LCD_DISPLAY_SINGLE_LINE   0x30         //������ʾ

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
#define LCD_Data P0        //LCD�����ݿ�
sbit LCD_BF=LCD_Data^7;    //LCDæ�ź�λ
sbit LCD_RS = P1^5;
sbit LCD_RW = P1^6;
sbit LCD_EN = P1^7;

/*�����ӳ���*/
void LCD_ClrAll(void);              //����
void Judge_LCD_busy(void);           //����Ƿ�æµ
void LCD_Write(uchar WriteData);     //д������
void LCD_write_data(uchar LCD_data); //д������ʾ
void LCD_cursor(uchar x);    //�����ʼ��ַ
void LCD_printc(unsigned char lcd_data) ;  //���һ���ַ�
void LCD_prints(unsigned char *lcd_string);//����ַ���

//void LCD_Back(void);

///*���ص�ԭ��*/    //����־��棿������
//void LCD_Back(void)
//{
 //LCD_Write(LCD_GO_HOME);
//}

//************************************************************************
/*LCD1602æµ�ж��ӳ���*/
void Judge_LCD_busy(void)   //�ж�LCD1602�Ƿ�æ״̬
{
 while(1)
  {
   LCD_EN=0;
   LCD_RS=0;
   LCD_RW=1;
   LCD_Data=0xff;
   LCD_EN=1;   //EN �� 1��0 ʹ��
   if(!LCD_BF)break; //LCD_BF=1��ʾæµ����Ҫ�ȴ���
  }
   LCD_EN=0;
}
/******LCD����***************/
void LCD_ClrAll(void)
{

 Judge_LCD_busy();   //�ж��Ƿ�æµ
 LCD_RS=0;
 LCD_RW=0;
 LCD_Data=0x01;
 LCD_EN=1;
 LCD_EN=0;

}
/*******LCDд���ݶ������ģʽ*********/
void LCD_Write(uchar WriteData)   //дָ�LCD
{
 Judge_LCD_busy();
 LCD_RS=0;
 LCD_RW=0;

 LCD_Data=WriteData; //��WriteData�������͵����ݿ�
 LCD_EN=1;
 LCD_EN=0;
 }
/********LCD��ʾ����***********/
void LCD_write_data(uchar LCD_data)      //���һ���ֽ����ݵ�LCD
{
 Judge_LCD_busy();
 LCD_RS=1;
 LCD_RW=0;

 LCD_Data=LCD_data;
 LCD_EN=1;
 LCD_EN=0;
 }


/****���λ�õ�ȷ��***/
void LCD_cursor(uchar x)            //LCD��궨λ��x��
{
 LCD_Write(0x80+x);                       //��һ�е�ַ��0x80

}


/*���һ���ַ�*/
void LCD_printc(unsigned char lcd_data)
{
 LCD_write_data(lcd_data);
}

/*����ַ���*/
void LCD_prints(unsigned char *lcd_string)
{
 unsigned char i=0;
 while(lcd_string[i]!=0x00)
  {
   LCD_write_data(lcd_string[i]);
   i++;
  }
}

/*��ʼ������*/
void LCD_initial(void)                        //��ʼ��LCD
{
 LCD_Write(LCD_AC_AUTO_INCREMENT|LCD_MOVE_DISENABLE);
 LCD_Write(LCD_DISPLAY_ON|LCD_CURSOR_OFF);
 LCD_Write(LCD_DISPLAY_DOUBLE_LINE);
 LCD_ClrAll();
}


#endif
