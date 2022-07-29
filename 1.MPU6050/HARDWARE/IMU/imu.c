#include "imu.h"
#include "mpu6050.h"
#include "usart.h"
#include <math.h>

/*************************************************
���ټ��� 1/Sqrt(x)
*************************************************/
float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

/***************************************************
��ȡIMUԭʼ����
***************************************************/
void Get_IMU_Date(Float_XYZ* gyro, Float_XYZ* acc)
{
	short gyrox,gyroy,gyroz;//������ԭʼ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	
	//��ȡIMU�������
	MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);//������ԭʼ����
	MPU_Get_Accelerometer(&aacx, &aacy, &aacz);//���ٶȼ�ԭʼ����
	
	//������ԭʼ����
	gyro->x = gyrox / 16.4 * PI / 180;	//����������Ϊ��2000��/s������������Ϊ16.4LSB/��/s
	gyro->y = gyroy / 16.4 * PI / 180;	//���������ݳ���16.4�õ����ǽǶȣ��ڽ�����Ԫ������ʱ��Ҫ����ת��Ϊ����
	gyro->z = gyroz / 16.4 * PI / 180;
//	gyro->x = gyrox;
//	gyro->y = gyroy;
//	gyro->z = gyroz;
	
	//���ٶȼ�ԭʼ����
	acc->x = aacx;
	acc->y = aacy;
	acc->z = aacz;
}

/*************************************************
Myhony��̬����
*************************************************/
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;		//��Ԫ��
float exInt = 0, eyInt = 0, ezInt = 0;	//�����������

//void IMU_Update(Float_XYZ* Gyro, Float_XYZ* Acc, Float_Angle* Angle)//����IMU��ԭʼ����
void IMU_Update(Float_XYZ* Gyro, Float_XYZ* Acc, Float_Angle* Angle)//����IMU��ԭʼ����,��ýǶ�
{
	float gx = Gyro->x, gy = Gyro->y, gz = Gyro->z;	//������ԭʼ���ݸ�ֵ���򻯼������
	float ax = Acc->x, ay = Acc->y, az = Acc->z;	//���ٶȼ�ԭʼ���ݸ�ֵ���򻯼������
	float vx, vy, vz;		//���۵ļ��ٶ�
	float ex, ey, ez;		//���ۼ��ٶ���ʵ�ʼ��ٶ�֮������
	float norm;		//���ڹ�һ��
	
	float q0q0 = q0 * q0;
	float q0q1 = q0 * q1;		//���ڼ���
	float q0q2 = q0 * q2;
	float q0q3 = q0 * q3;
	float q1q1 = q1 * q1;
	float q1q2 = q1 * q2;
	float q1q3 = q1 * q3;
	float q2q2 = q2 * q2;
	float q2q3 = q2 * q3;
	float q3q3 = q3 * q3;
	
	//���ٶȼƲ�����������������������ϵ�£�
	norm = invSqrt(ax*ax + ay*ay + az*az);
	ax = ax * norm;
	ay = ay * norm;
	az = az * norm;
	
	//�����ǻ��ֹ�����������ٶ���������������ϵ�£�  Ϊʲôv����Ҫ��λ��
	vx = 2*(q1q3 - q0q2);
	vy = 2*(q0q1 + q2q3);
	vz = q0q0 - q1q1 - q2q2 + q3q3;
	
	//��������������������������������������������
	ex = (ay*vz - az*vy);
	ey = (az*vx - ax*vz);
	ez = (ax*vy - ay*vx);
	
	//������������л���
	exInt = exInt + ex*Ki*halfT;
	eyInt = eyInt + ey*Ki*halfT;
	ezInt = ezInt + ez*Ki*halfT;
	
	//�����PI���κ󲹳���������
	gx =gx + Kp*ex + exInt;
	gy =gy + Kp*ey + eyInt;
	gz =gz + Kp*ez + ezInt;//gz����û�й۲��߽���У�������Ư�ƣ����ֳ����ֵ����������Լ�����̫�������飩
	
	//��Ԫ��΢�ַ���
	q0 = q0 + (-q1*gx - q2*gy - q3*gz) * halfT;
	q1 = q1 + (q0*gx + q2*gz - q3*gy) * halfT;
	q2 = q2 + (q0*gy - q1*gz + q3*gx) * halfT;
	q3 = q3 + (q0*gz + q1*gy - q2*gx) * halfT;
	
	//��λ����Ԫ��������Ϊɶ��λ����
	norm = invSqrt(q0*q0 + q1*q1 + q2*q2 +q3*q3);
	q0 = q0 * norm;
	q1 = q1 * norm;
	q2 = q2 * norm;
	q3 = q3 * norm;
	
	//��Ԫ��ת����ŷ����
	Angle->pitch = asin(2.0f * (q1q3 - q0q2)) * RAD2DEG;
	Angle->roll = atan2(2.0f*q2q3 + 2.0f*q0q1, q0q0 - q1q1- q2q2 + q3q3) * RAD2DEG;
	Angle->yaw = atan2(2.0f*(q1q2 + q0q3), q0q0 + q1q1- q2q2 - q3q3) * RAD2DEG;
	
}






















