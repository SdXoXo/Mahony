#ifndef __IMU_H
#define __IMU_H	 
#include "sys.h"


#define	Kp			15.0f		//��������
#define	Ki			0.005f	//��������
#define	halfT		0.001f	//�������ڵ�һ��

#define DEG2RAD  	0.017453293f //��ת���Ȧ�/180 
#define RAD2DEG  	57.29578f    //����ת��180/�� 
#define PI				3.141592654f

//������������Ǻ�������ٶȼƵ�����
typedef struct 
{
	float x;
	float y;
	float z;
}Float_XYZ;


//����������̬��
typedef struct 
{
	float pitch;	//������
	float roll;		//�����
	float yaw;		//�����
}Float_Angle;



void Get_IMU_Date(Float_XYZ* gyro, Float_XYZ* acc);//��ȡIMUԭʼ����
void IMU_Update(Float_XYZ* Gyro, Float_XYZ* Acc, Float_Angle* Angle);//��̬����

		 				    
#endif


