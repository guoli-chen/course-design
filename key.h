//*****************************************
//����4*4����ͷ�ļ� 
//�ļ�����Ҫ����˵��
// key_c����>����io��
// KeyValue_c����>�п� 
// KeyValue_v����>�п�
// *KeyValue����>ָ������ ����lcd1602��ʾ�ַ����ͱ��������洢�ַ���
//�ļ��к���˵�� 
// keyscanner(void) ����ֵΪָ������ 
// ps ����ʱ return KeyValue����
// �ڵ��ô˺���ʱ ���պ�������ֵ�ı�������Ϊָ������
// lcd1602�ڴ���ʱ���ڱ�������Ϊָ�� ��˲���Ҫ��ַȡֵ&
//lcd1602Ӧ�þ���
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

typedef unsigned int uint;         //���������ͽ�����������
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
	if(key_c!=0x0f)//��ȡ�����Ƿ���
        {
                delay(1000);//��ʱ10ms��������
                if(key_c!=0x0f)//�ٴμ������Ƿ���
                {       
                        /*���н��в��ԣ���λ�͵�ƽ����λ�ߵ�ƽ��*/
                        key_c=0x0F;
                    	KeyValue_c=key_c;
						delay(100);
                        /*���н��в��ԣ���λ�ߵ�ƽ����λ�͵�ƽ��*/
                        key_c=0xF0;
						KeyValue_v=key_c;
                       switch(KeyValue_c|KeyValue_v)
                        {        /*��һ�ж�Ӧ���кż�����Ӧ�й��ɵ��ֺž͵��ڰ����ţ�����ԭ��ͼ�鿴*/
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

