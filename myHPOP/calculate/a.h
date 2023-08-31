#ifndef _A_H_
#define _A_H_
#include<math.h>
#include"ODE45.h"
#include"timecoor.h"
#include"SOFA/sofa.h"
#include"SOFA/sofam.h"
#include"nrlmsise00/nrlmsise-00.h"
#include"jpl/jpleph.h"
#include"jpl/jpl_int.h"

//��һ������гϵ��
void CS(double n, double m, double* Cnm, double* Snm);
//��һ�������õ¶���ʽ
double P(double n, double m, double u);
//���ع�ֱ������ϵ�е�ֱ������ת����������ϵ��
void ecf2sph(double* recf, double* e1, double* e2, double* e3);

//�����������ٶȣ����������㶯���ٶȣ�
void J(double* recf, double Re, double mu, double* a1, double* a2);
//��������
void D(double* ad, double* r, double* v, double date1, double date2, double omegaev, double Re, double fe, double Cd, double Sm, double Fa, double F, double Ap);
//̫����ѹ��
void R(double* ar, double* r, double* rs, double Re, double c, double Sm, double Ls, double Cr);
//����������
void T(double* at, double* r, double* rs, double mus);

#endif // !_A-H_
