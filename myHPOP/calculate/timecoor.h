#ifndef _TIMECOOR_H_
#define _TIMECOOR_H_

#include"SOFA/sofa.h"
#include"SOFA/sofam.h"
#include"ODE45.h"

//三个轴坐标转换矩阵
void A(int n, double x, double* R);

//将J2000坐标系转换成地固坐标系的转换矩阵
void J20002ecf(double date11, double date12, double* R);
//将地固坐标系转换成J2000坐标系的转换矩阵
void ecf2J2000(double date11, double date12, double* R);

#endif // !_TIMECOOR_H_