#ifndef _ODE45_H_
#define _ODE45_H_
#include<math.h>
#include<iostream>
#include<stdio.h>

//fun:�����ֵ�һ��΢�ַ��̣�dxΪ΢�ַ����Ҷ��para��ֵ���������Ҫ�õ���һЩ����
//x:��ʼʱ��t0��״̬�����ֳɹ��󣬴����ĩ��tfʱ�̵�״̬
//n:Ϊx��ά����NumPoint:��ı䲽�����ֵ���
//AbsTol:nά�ľ�����RelTol:һά�������Ĭ��Ϊ1e-3
//NormControl:�����Ʒ�ʽ��Ĭ��Ϊ0��ȡ0����
//MaxStep:��󲽳����ƣ�Ĭ��ȡ-1����ʾ�����ƣ�һ�㲻����
//InitialStep:��ʼ�²ⲽ����Ĭ��ȡ-1����ʾ���²⣬�ɳ��Զ�ȷ��
//fid:�洢�ļ�·�������洢�䲽�����ֹ����У����ֵ��ʱ���״ֵ̬��Ĭ��ȡNULL����ʾ���洢�м�ֵ
//ode45��������1ʱ����ʾ���ֳɹ������򲻶�
int ode45(int (*fun)(double t, const double* x, double* dx, const double* para), double* x, const double* para,
		  double t0, double tf, int n, int& NumPoint, const double* AbsTol, double RelTol=1.0e-3,
		  int NormControl=0, double MaxStep=-1, double InitialStep=-1, FILE* fid=NULL);

//���ź���
template<class T> inline int sign(const T & x)
{
	if(x>0)
		return 1;
	else if(x<0)
		return -1;
	else
		return 0;
}

//�����ֵ
template <class T>
inline T max(T x, T y) 
{ 
	return (x>y)?x:y;
}


//����Сֵ
template <class T>
inline T min(T x, T y) 
{
	return (x<y)?x:y;
}

//����
double norm(const double* vec, int n, int type);

//����
void cross(double* a1, double* a2, double* a);

//��˷�
double exponent(double x, int n);

//��������
void matrixmulti(double* R1, double* R2, double* R, int type);

//�����ת��
void matrixtrans(double* R);

#endif