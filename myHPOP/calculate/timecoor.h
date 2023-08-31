#ifndef _TIMECOOR_H_
#define _TIMECOOR_H_

#include"SOFA/sofa.h"
#include"SOFA/sofam.h"
#include"ODE45.h"

//����������ת������
void A(int n, double x, double* R);

//��J2000����ϵת���ɵع�����ϵ��ת������
void J20002ecf(double date11, double date12, double* R);
//���ع�����ϵת����J2000����ϵ��ת������
void ecf2J2000(double date11, double date12, double* R);

#endif // !_TIMECOOR_H_