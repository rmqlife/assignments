//#include <reg52.h>     //包括一个 52 标准内核的头文件
#include <AT89X51.H>
const unsigned int INT11=63441;
#define KEY P2
#define LCD_DATA P1
#define LCD_E P3_5
#define LCD_RW P3_6
#define LCD_RS P3_7
const char KEYIN[4]={0xfe,0xfd,0xfb,0xf7};
const char KEYOUT[4]={0xe0,0xd0,0xb0,0x70};
unsigned char j,k;
void delay(unsigned char i)
{
for(j=i;j>0;j--)
	for(k=125;k>0;k--)
	{}
}


void ti0() interrupt 1
{
	TH0=0xF7;	 //set init 65536-60000
	TL0=0xD1;	 //set init	65536-60000
	P1_0=!P1_0;
}


void key16() interrupt 0
{
	P1_0=!P1_0;
	delay();
}


void setuptimer()
{
   	ET0=0;
	TMOD=1;	//16bit counter
	TH0=0xF7;	 //set init 65536-60000
	TL0=0xD1;	 //set init	65536-60000
	//T0=INT11;
	TR0=1; //start counter
	//TF0==1 count finished
	EA=1; //enable all interrupt 
	ET0=1; //enable timer0 interrupt
	//EX0=1;//enable external0 interrupt 
}

void setupOI()//out interrupt
{
	EA=1;
	EX0=1;
	IT0=1;//下沿触发
}

void show()
{
	P1_0=!P1_0;
}

void lcd_wc(unsigned char command)//write command
{
LCD_DATA=command;
LCD_RS=0;
LCD_RW=0;
LCD_E=0;
delay(5);
LCD_E=1;
}

void lcd_wd(unsigned char lcddata)//write data
{
LCD_DATA=lcddata;
LCD_RS=1;
LCD_RW=0;
LCD_E=0;
delay(5);
LCD_E=1;
}


void lcd_init()
{
lcd_wc(0x38);//start to show
lcd_wc(0x0f);//show,cursor,twinkle
lcd_wc(0x07);//from left to right and move screen
lcd_wc(0x02);//set the cursor to 0,0

}

void lcd_clear()
{
lcd_wc(0x01);
}




unsigned char t,m,temp;
void main()
{
	P1=0;	
	//setupOI();
	//setup timer
	lcd_clear();
	lcd_init();


	
	while (1)
	{
	lcd_wd('a');
	for (t=0;t<4;t++)
	{
		KEY=KEYIN[t];
		temp=KEY;
		temp=temp & 0xf0;//& f :stay, &	0 :clear
		if (temp!=0xf0)
		{
		delay(10);
		if (temp!=0xf0)
			{
			delay(10);
			//if (temp!=0xf0)
			for (m=0;m<4;m++)
				if (temp==KEYOUT[m])	
					{
					//show();
					break;
					//coordinate t,m
					}
			}
		}
	}//for				
	}//while
}