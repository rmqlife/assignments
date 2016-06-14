//#include <at89x51.h>//��AT89C51ʱ�������ͷ�ļ�
#include <reg52.h>//�û���W78E58Bʱ���������ͷ�ļ�

sbit DQ = P3^4;			//����DQ����ΪP3.4

const unsigned char TEMPHIGH=110;
const unsigned char TEMPLOW=-20;


/***********ds18b20�ӳ��Ӻ���������12MHz ��*******/ 
/************DS18B20��ʱ��Ҫ�����,��ֻ�ܳ����ܶ�
*************��11.0592M��Ҳ��,��Ϊʱ�䳤Щ********/
void delay_18B20(unsigned int i)
{
	while(i--);
}

/**********ds18b20��ʼ������**********************/

void Init_DS18B20(void) 
{
	 unsigned char x=0;
	 DQ = 1;          //DQ��λ
	 delay_18B20(8);  //������ʱ
	 DQ = 0;          //��Ƭ����DQ����
	 delay_18B20(80); //��ȷ��ʱ ���� 480us
	 DQ = 1;          //��������
	 delay_18B20(14);
	 x=DQ;            //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
	 delay_18B20(20);
}

/***********ds18b20��һ���ֽ�**************/  

unsigned char ReadOneChar(void)
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	 {
		  DQ = 0; // �������ź�
		  dat>>=1;
		  DQ = 1; // �������ź�
		  if(DQ)
		  dat|=0x80;
		  delay_18B20(4);
	 }
 	return(dat);
}

/*************ds18b20дһ���ֽ�****************/  

void WriteOneChar(unsigned char dat)
{
 	unsigned char i=0;
 	for (i=8; i>0; i--)
 	{
  		DQ = 0;
 		DQ = dat&0x01;
    	delay_18B20(5);
 		DQ = 1;
    	dat>>=1;
 }
}

/**************��ȡds18b20��ǰ�¶�************/

unsigned char *ReadTemperature(char TH,char TL,unsigned char RS)
{	unsigned char tt[2];
	Init_DS18B20();
	WriteOneChar(0xCC);    	// ����������кŵĲ���
	WriteOneChar(0x4E); 	// //д��"д�ݴ���"����,�޸�TH��TL�ͷֱ������üĴ���
							//��дTH,��дTL,���д���üĴ���
	WriteOneChar(TH);		//д�����趨���¶ȱ�������
	WriteOneChar(TL);		//д�����趨���¶ȱ�������
	WriteOneChar(RS);		//д���üĴ���,��ʽΪ0 R1 R0 1,1 1 1 1
							//R1R0=00�ֱ���¦9λ,R1R0=11�ֱ���Ϊ12λ

	delay_18B20(80);       // this message is wery important
	Init_DS18B20();
	WriteOneChar(0xCC);    	// ����������кŵĲ���
	WriteOneChar(0x44); 	// �����¶�ת��

	delay_18B20(80);       // this message is wery important
	Init_DS18B20();
	WriteOneChar(0xCC); 	//����������кŵĲ���
	WriteOneChar(0xBE); 	//��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
	delay_18B20(80);

	tt[0]=ReadOneChar();    	//��ȡ�¶�ֵ��λ
	tt[1]=ReadOneChar();   		//��ȡ�¶�ֵ��λ
	return(tt);
}