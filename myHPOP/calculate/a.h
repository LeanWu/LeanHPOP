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

//归一化的球谐系数
void CS(double n, double m, double* Cnm, double* Snm);
//归一化的勒让德多项式
double P(double n, double m, double u);
//将地固直角坐标系中的直角坐标转换到球坐标系中
void ecf2sph(double* recf, double* e1, double* e2, double* e3);

//地球引力加速度（含非球形摄动加速度）
void J(double* recf, double Re, double mu, double* a1, double* a2);
//大气阻力
void D(double* ad, double* r, double* v, double date1, double date2, double omegaev, double Re, double fe, double Cd, double Sm, double Fa, double F, double Ap);
//太阳光压力
void R(double* ar, double* r, double* rs, double Re, double c, double Sm, double Ls, double Cr);
//第三体引力
void T(double* at, double* r, double* rs, double mus);

#endif // !_A-H_
