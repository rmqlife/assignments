#ifndef REMOTE_H
#define REMOTE_H

#include "reg52.h"


unsigned char Remote_CY[4];						//NECΪ�ĸ��ֽ�����
bit Remote_FAG;								//�ɹ����ձ�־
sbit Remote_PIN=P3^3;		//���������սţ�outside interrupt			
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
	EA=1;					//���ȿ������ж�
	EX1=1;  				//�����ⲿ�ж� 1
	IT1=1;        			//���ó��½��ش�����ʽ
	TMOD=0X10;				//��ʱ��1�ķ�ʽ1��16λ����������������ʱ��
	Remote_FAG=0;
}


/*************��ʱ�Ӻ��� ********************************************************/
void Remote_Delay(unsigned char timer)								
{
	while(timer--);
}

/***********���ж�1��ں�����P33���ţ������߽���IC���ݽ�**************************/
void Remote_Check(void)   interrupt 2
{
	unsigned char i,ia;
	/**************��ʼ�ж��Ƿ�ΪNEC�����������ǰ9MS******************************/
	TL1=0;
	TH1=0;				//��ʱ/������1��ʼֵ
	TR1=1;				//��ʱ����12M����12��Ƶ��������1us����
	while(!Remote_PIN){		//���ŵ͵�ƽʱ�Ĵ���	
		Remote_Delay(10);		//͢ʱ������Ƶ����ȡ������ֵ�����ã��ɲ��á�
		if(TH1>40)		//����Ϊ���źŴ��������,������40�ļ���ֵ��Ҫ�˳�,��ΪNEC���������Ϊ9MS������Լ9000��TH1Լ����35
			return;		
	}
	TR1=0;				//�źŷ�תֹͣ����
	if(TH1<30)			//��Ҫ�ж�С��30Ϊ��NEC�Ʊ����˳�,���������������
		return;

	TH1=0;				//��ʱ/������1��ʼֵ
	TR1=1;
	while(Remote_PIN){			//������ĺ�4��5MS�ߵ�ƽʱ�ȴ�
		Remote_Delay(10);
		if(TH1>25)		//4��5MS��Լ����17
			return;		
	}

	/***********��ʼ�����ĸ��ֽ�����**************************************/	
	for(i=0;i<4;i++){
		for(ia=0;ia<8;ia++){
			//�͵�ƽ��ʼ��������ֻ�ȴ��ߵ�ƽ��������Ϊ���жϴ����ź�ʱ�˳�
			TH1=0;					//��ʱ������1��ʼֵ
			TR1=1;					//��������
			while(!Remote_PIN){			//���յ͵�ƽʱ����
				Remote_Delay(10);
				if(TH1>15)
					return;			//�����ź��˳�
			}
			//�͵�ƽ����			
			//�ߵ�ƽ��ʼ��
			TH1=0;
			while(Remote_PIN){
				Remote_Delay(10);
				if(TH1>15)		
					return;		
			}
			TR1=0;
			//�ߵ�ƽ�������ж�����1��0���������
			Remote_CY[i]>>=1;			//�����ɸ�λ�����λ
			if(TH1>4)				//ʱ����TH1����4��������1MS�ж�Ϊ1
				Remote_CY[i]|=0x80;
		}
	}
	if(Remote_CY[2]+Remote_CY[3]==0xff)
		Remote_FAG=1;	//���ճɹ�
	TF1=0;
}


char Remote_Key()
{
	return Remote_Table[Remote_CY[2]];
}
#endif