//*****************************************
//自制4*4按键头文件 
//文件中主要变量说明
// key_c——>按键io口
// KeyValue_c——>列口 
// KeyValue_v——>行口
// *KeyValue——>指针类型 由于lcd1602显示字符类型变量用来存储字符串
//文件中函数说明 
// keyscanner(void) 返回值为指针类型 
// ps 返回时 return KeyValue即可
// 在调用此函数时 接收函数返回值的变量类型为指针类型
// lcd1602在传参时由于变量类型为指针 因此不需要地址取值&
//lcd1602应用举例
//uchar *keyy;
//void main()
//{	
//    LCD_init();
//    while(1)
//    {
//	    keyy=keyscanner();
//      string(0x80,keyy);
//	  }
//	
//}  
//********************************************* 





#ifndef _keypoint_H
#define _keypoint_H

#include "intrins.h"
#include "reg51.h"
#define key_c P1

typedef unsigned int uint;         //对数据类型进行声明定义
typedef unsigned char uchar;

uint KeyValue_c;
uint KeyValue_v;
uchar *KeyValue;
void delay(uint i)
{
        while(i--);     
}
uchar* keyscanner()
{
	key_c=0x0f;
	if(key_c!=0x0f)//读取按键是否按下
        {
                delay(1000);//延时10ms进行消抖
                if(key_c!=0x0f)//再次检测键盘是否按下
                {       
                        /*对列进行测试（高位低电平，低位高电平）*/
                        key_c=0x0F;
                    	KeyValue_c=key_c;
						delay(100);
                        /*对行进行测试（低位高电平，高位低电平）*/
                        key_c=0xF0;
						KeyValue_v=key_c;
                       switch(KeyValue_c|KeyValue_v)
                        {        /*上一行对应的列号加上相应有规律的字号就等于按键号，可由原理图查看*/
                                case(0X77): KeyValue="1";break; 
                                case(0Xb7): KeyValue="2";break; 
                                case(0Xd7): KeyValue="3";break;
                                case(0Xe7): KeyValue="4";break;
								case(0X7b): KeyValue="5";break; 
                                case(0Xbb): KeyValue="6";break; 
                                case(0Xdb): KeyValue="7";break;
                                case(0Xeb): KeyValue="8";break;
								case(0X7d): KeyValue="9";break; 
                                case(0Xbd): KeyValue="10";break; 
                                case(0Xdd): KeyValue="11";break;
                                case(0Xed): KeyValue="12";break;
								case(0X7e): KeyValue="13";break; 
                                case(0Xbe): KeyValue="14";break; 
                                case(0Xde): KeyValue="15";break;
                                case(0Xee): KeyValue="16";break;
                        }
                        
                }
        }
        return KeyValue;
}
#endif

