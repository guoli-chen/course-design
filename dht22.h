#ifndef _dht22_H
#define _dht22_H

#include "reg51.h"
#include "intrins.h"
#include "lcd1602.h"

sbit Bus=P2^4;
uchar value[5];
uint hum,temp;


void Delay20us(void)   //误差 0us
{
    unsigned char a,b;
    for(b=3;b>0;b--)
        for(a=1;a>0;a--);
}


void Delay1ms(uchar d)   //误差 0us
{
    unsigned char a,b,c;
	for(; d>0;d--)
    for(c=1;c>0;c--)
	{
        for(b=142;b>0;b--)
		{
            for(a=2;a>0;a--); 
		}
	}
}

/************************读值函数******************************/
void Read_value()
{	
	uchar i,j=0,mask;
	Bus=0;//主机拉低总线至少1ms(20ms)
	Delay1ms(20);
	Bus=1;//主机主动拉高20us
	while(Bus);//等待从机拉低总线
	while(!Bus);//度过从机拉低时间
	while(Bus);//度过从机拉高时间
	while(j<5)
	{
		mask=0x80;
		for(i=0;i<8;i++)
		{
			while(!Bus);//度过数据位的低电平
			Delay20us();//延迟40us后进行电平检测
			Delay20us();		
			if(Bus==0)
			{
				value[j]&=(~mask);
			}
			else
			{
				value[j]|=mask;
			}
			mask>>=1;
			while(Bus);//度过剩余高电平（如果是1的话）
		}
		j++;
	}

}

void display()
{	  char addf=0x89;
 	  char adds=0xc9;
	  uint tg=0,hg=0;
	  string_s(0x80,"Hum:");
	  string_s(0xc0,"Temp:");
	  while(hum>0)
	  {
	  	 switch(hum%10)
		 {
		  case 0:string(addf,'0');addf--;break;
		  case 1:string(addf,'1');addf--;break;
		  case 2:string(addf,'2');addf--;break;
		  case 3:string(addf,'3');addf--;break;
		  case 4:string(addf,'4');addf--;break;
		  case 5:string(addf,'5');addf--;break;
		  case 6:string(addf,'6');addf--;break;
		  case 7:string(addf,'7');addf--;break;
		  case 8:string(addf,'8');addf--;break;
		  case 9:string(addf,'9');addf--;break;

		 }
		 if(hg==0){string(0x88,'.');addf--;hg++;}
		  hum=hum/10;
	  }
	  while(temp>0)
	  {
	  	 switch(temp%10)
		 {
		  case 0:string(adds,'0');adds--;break;
		  case 1:string(adds,'1');adds--;break;
		  case 2:string(adds,'2');adds--;break;
		  case 3:string(adds,'3');adds--;break;
		  case 4:string(adds,'4');adds--;break;
		  case 5:string(adds,'5');adds--;break;
		  case 6:string(adds,'6');adds--;break;
		  case 7:string(adds,'7');adds--;break;
		  case 8:string(adds,'8');adds--;break;
		  case 9:string(adds,'9');adds--;break;

		 }
		 if(tg==0){string(0xc8,'.');adds--;tg++;}
		  temp=temp/10;
	  }
}
void main()
{  
   	LCD_init();   //lcd1602初始化
   	while(1){
	Delay1ms(2000);
	Read_value();
	hum=value[0]*256+value[1];//计算湿度值
	temp=(value[2]&0x7f)*256+value[3];//如果温度为负值,则&0x3f去掉符号位后再计算；若为正值则无影响
	display();  
   } 
}
#endif
