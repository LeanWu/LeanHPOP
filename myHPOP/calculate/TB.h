#ifndef _TB_H_
#define _TB_H_
#include"ODE45.h"
#include"SOFA/sofa.h"
#include"SOFA/sofam.h"
#include"timecoor.h"
#include"a.h"

//将轨道根数转换成位置速度
void rorbit(double a, double e, double i, double Omega, double omega, double f, double mu,double *rv);

//求解方程
void TBAll(double* rv, int* t1, int* t2, double fd1, double fd2, double* para,int *numpoint);

#endif // !_TB_H_
