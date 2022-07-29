#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

typedef union     //����ṹ�壬�ο�https://blog.csdn.net/ls667/article/details/50811519����
{
	float fdata;
	unsigned long ldata;
}FloatLongType;

void Float_to_vofa_byte(float f,unsigned char vofa_byte[]);

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
#endif


