#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "mpu6050.h"
#include "timer.h"
#include "imu.h"
/*************************************ȫ�ֱ�������*************************************************/
//MPU6050
Float_XYZ gyro;
Float_XYZ acc;
Float_Angle angle;


int main(void)
{
/*************************************��������*************************************************/
	//����
	
	//VOFA��λ��
	u8 vofa_i = 0;//VOFA��λ��ѭ������
	u8 vofa_byte[4] = {0};//VOFA��λ������
	u8 vofa_date[4] = {0};
	 
/*************************************��ʼ������*************************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    	//��ʱ������ʼ��	  
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	LED_Init();					//LED��ʼ��
	MPU_Init(); 	//��ʼ��MPU6050
	TIM3_Int_Init(19, 7199);	//2ms�ж�
	
  while(1)
	{
//		//���Է���
//		Float_to_vofa_byte(1000.0, vofa_byte);  
//		for(vofa_i=0; vofa_i<4; vofa_i++)
//		{
//			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//		}	
		
//		//����MPU���¶�
//		Float_to_vofa_byte(tempt*0.01, vofa_byte);  
//		for(vofa_i=0; vofa_i<4; vofa_i++)
//		{
//			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//		}	

//		//����������x��ԭʼ����
//		Float_to_vofa_byte(gyro.x, vofa_byte);  
//		for(vofa_i=0; vofa_i<4; vofa_i++)
//		{
//			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//		}			
//		
//		//����������y��ԭʼ����
//		Float_to_vofa_byte(gyro.y, vofa_byte);  
//		for(vofa_i=0; vofa_i<4; vofa_i++)
//		{
//			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//		}	

//		//����������z��ԭʼ����
//		Float_to_vofa_byte(gyro.z, vofa_byte);  
//		for(vofa_i=0; vofa_i<4; vofa_i++)
//		{
//			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//		}	

//		//���ͼ��ٶȼ�x��ԭʼ����
//		Float_to_vofa_byte(acc.x, vofa_byte);  
//		for(vofa_i=0; vofa_i<4; vofa_i++)
//		{
//			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//		}

//		//���ͼ��ٶȼ�y��ԭʼ����
//		Float_to_vofa_byte(aacy*1.0, vofa_byte);  
//		for(vofa_i=0; vofa_i<4; vofa_i++)
//		{
//			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//		}		

//		//���ͼ��ٶȼ�z��ԭʼ����
//		Float_to_vofa_byte(aacz*1.0, vofa_byte);  
//		for(vofa_i=0; vofa_i<4; vofa_i++)
//		{
//			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//		}

		//���͸���������
		Float_to_vofa_byte(angle.pitch, vofa_byte);  
		for(vofa_i=0; vofa_i<4; vofa_i++)
		{
			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		}
		
		//���ͺ��������
		Float_to_vofa_byte(angle.roll, vofa_byte);  
		for(vofa_i=0; vofa_i<4; vofa_i++)
		{
			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		}
		
		//���ͺ��������
		Float_to_vofa_byte(angle.yaw, vofa_byte);  
		for(vofa_i=0; vofa_i<4; vofa_i++)
		{
			USART_SendData(USART1, vofa_byte[vofa_i]);         //�򴮿�1��������
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		}
		
		//����֡β
		vofa_date[0]=0X00;vofa_date[1]=0X00;
		vofa_date[2]=0X80;vofa_date[3]=0X7f;
		for(vofa_i=0;vofa_i<4;vofa_i++)
		{
			USART_SendData(USART1, vofa_date[vofa_i]);         //�򴮿�3��������
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		}

	}	 
} 

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
		
		Get_IMU_Date(&gyro, &acc);//��ȡIMUԭʼ����
		IMU_Update(&gyro, &acc, &angle);
	}
}










