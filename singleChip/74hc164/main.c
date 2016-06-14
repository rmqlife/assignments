#include "lcd1602.h"
#include "remote.h"


void main()
{
LCD_Init();
LCD_Write_String(0,0,"hello 164");
while(1)
{
//Transfer(0xff);
//char k=waitkey();
//LCD_Write_Char(1,1,k);
}


}
