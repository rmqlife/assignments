#ifndef KEY_H
#define KEY_H
#include <reg52.H>
#define KEY P2
const char KEYIN[4]={0xfe,0xfd,0xfb,0xf7};
const char KEYOUT[4]={0xe0,0xd0,0xb0,0x70};
const char KEYIMAGE[16]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
unsigned char j,k;



void Key_Delay(unsigned char i)
{
for(j=i;j>0;j--)
	for(k=125;k>0;k--)
	{}
}
unsigned char t,temp,m;

unsigned char waitkey()
{
	while (1)
	{
	for (t=0;t<4;t++)
	{
		KEY=KEYIN[t];
		temp=KEY;
		temp=temp & 0xf0;//& f :stay, &	0 :clear
		if (temp!=0xf0)
		{
		Key_Delay(10);
		if (temp!=0xf0)
			{
			Key_Delay(10);
			//if (temp!=0xf0)
			for (m=0;m<4;m++)
				if (temp==KEYOUT[m])	
					{
					return KEYIMAGE[m+t*4];
					//coordinate t,m
					}
			}
		}
	}//for				
	}//while

}

#endif