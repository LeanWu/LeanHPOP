#ifndef _ODE45_H_
#define _ODE45_H_
#include<math.h>
#include<iostream>
#include<stdio.h>

//fun:被积分的一阶微分方程，dx为微分方程右端项，para数值传入可能需要用到的一些参数
//x:初始时刻t0的状态，积分成功后，存的是末端tf时刻的状态
//n:为x的维数，NumPoint:存的变步长积分点数
//AbsTol:n维的绝对误差，RelTol:一维的相对误差，默认为1e-3
//NormControl:误差控制方式，默认为0，取0即可
//MaxStep:最大步长限制，默认取-1，表示不限制，一般不限制
//InitialStep:起始猜测步长，默认取-1，表示不猜测，由程自动确定
//fid:存储文件路径名，存储变步长积分过程中，积分点的时间和状态值，默认取NULL，表示不存储中间值
//ode45返回整数1时，表示积分成功，否则不对
int ode45(int (*fun)(double t, const double* x, double* dx, const double* para), double* x, const double* para,
		  double t0, double tf, int n, int& NumPoint, const double* AbsTol, double RelTol=1.0e-3,
		  int NormControl=0, double MaxStep=-1, double InitialStep=-1, FILE* fid=NULL);

//符号函数
template<class T> inline int sign(const T & x)
{
	if(x>0)
		return 1;
	else if(x<0)
		return -1;
	else
		return 0;
}

//求最大值
template <class T>
inline T max(T x, T y) 
{ 
	return (x>y)?x:y;
}


//求最小值
template <class T>
inline T min(T x, T y) 
{
	return (x<y)?x:y;
}

//求范数
double norm(const double* vec, int n, int type);

//求叉乘
void cross(double* a1, double* a2, double* a);

//求乘方
double exponent(double x, int n);

//求矩阵相乘
void matrixmulti(double* R1, double* R2, double* R, int type);

//求矩阵转置
void matrixtrans(double* R);

#endif