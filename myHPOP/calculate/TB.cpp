#include"TB.h"

char ephemeris_filename[]="../myHPOP/calculate/jpl/de405.bin";

void rorbit(double a, double e, double i, double Omega, double omega, double f, double mu, double* rv)
{
	double p, r0, h0;
	double A1[9], A2[9], A3[9], T[9], I[9], r1[3] = { 0 }, v1[3] = { 0 }, r[3], v[3];
	p = a * (1 - e * e);
	r0 = p / (1 + e * cos(f));
	h0 = sqrt(mu * p);

	A(3, Omega, A1); A(1, i, A2); A(3, omega + f, A3);
	matrixmulti(A1, A2, T, 1); matrixmulti(T, A3, I, 1);
	r1[0] = r0;
	v1[0] = (mu * e * sin(f)) / h0;
	v1[1] = (mu * (1 + e * cos(f))) / h0;

	matrixmulti(I, r1, r, 0);
	matrixmulti(I, v1, v, 0);
	rv[0] = r[0]; rv[1] = r[1]; rv[2] = r[2];
	rv[3] = v[0]; rv[4] = v[1]; rv[5] = v[2];
}

int TBFun0(double t, const double* x, double* dx, const double* para)
{
	double mu = para[0];
	double r = norm(x, 3, 2);
	double C = -mu / (r * r * r);
	int i;
	for (i = 0; i < 3; i++)
	{
		dx[i] = x[3 + i];
		dx[3 + i] = C * x[i];
	}
	return 1;//一切顺利，就返回1，告诉调用它的函数，计算正常，否则返回0
}

int TBFun1(double t, const double* x, double* dx, const double* para)
{
	double taia1 = *para;
	double taib1 = *(para + 1);
	double taia2 = *(para + 2);
	double taib2 = *(para + 3);
	double mu = *(para + 4);
	double Re = *(para + 5);

	double rj2000[3], a0[3], a1[3], a2[3] = {0}, aj[3], recf[3], T[9];
	double r,tai1,tai2,date1,date2,C;
	int i;

	rj2000[0] = *x;
	rj2000[1] = *(x + 1);
	rj2000[2] = *(x + 2);
	r = norm(rj2000, 3, 2);

	tai1 = taia1;
	tai2 = taib1 + t / 86400;
	iauTaitt(tai1, tai2, &date1, &date2);

	for (i = 0; i < 3; i++)
	{
		a0[i] = -mu * rj2000[i] / (r * r * r);
	}

	J20002ecf(date1, date2, T); matrixmulti(T, rj2000, recf, 2);
	J(recf,Re,mu,a1,a2);
	ecf2J2000(date1, date2, T); matrixmulti(T, a2, aj, 2);
	for (i = 0; i < 3; i++)
	{
		dx[i] = x[3 + i];
		dx[3 + i] = a0[i]+aj[i];
	}
	
	return 1;//一切顺利，就返回1，告诉调用它的函数，计算正常，否则返回0
}

int TBFun2(double t, const double* x, double* dx, const double* para)
{
	double taia1 = *para;
	double taib1 = *(para + 1);
	double taia2 = *(para + 2);
	double taib2 = *(para + 3);
	double mu = *(para + 4);
	double omegaev = *(para + 5);
	double Re = *(para + 6);
	double fe = *(para + 7);
	double Cd = *(para + 8);
	double Sm = *(para + 9);
	double Fa = *(para + 10);
	double F = *(para + 11);
	double Ap = *(para + 12);

	double rj2000[3], v[3], a0[3], ad[3];
	double r, tai1, tai2, date1, date2;
	int i;

	rj2000[0] = *x;
	rj2000[1] = *(x + 1);
	rj2000[2] = *(x + 2);
	v[0] = *(x + 3);
	v[1] = *(x + 4);
	v[2] = *(x + 5);
	r = norm(rj2000, 3, 2);

	tai1 = taia1;
	tai2 = taib1 + t / 86400;
	iauTaitt(tai1, tai2, &date1, &date2);

	for (i = 0; i < 3; i++)
	{
		a0[i] = -mu * rj2000[i] / (r * r * r);
	}

	D(ad, rj2000, v, date1, date2, omegaev, Re, fe, Cd, Sm, Fa, F, Ap);

	for (i = 0; i < 3; i++)
	{
		dx[i] = x[3 + i];
		dx[3 + i] = a0[i] + ad[i];
	}

	return 1;//一切顺利，就返回1，告诉调用它的函数，计算正常，否则返回0
}

int TBFun3(double t, const double* x, double* dx, const double* para)
{
	double taia1 = *para;
	double taib1 = *(para + 1);
	double taia2 = *(para + 2);
	double taib2 = *(para + 3);
	double mu = *(para + 4);
	double Re = *(para + 5);
	double c = *(para + 6);
	double Sm = *(para + 7);
	double Ls = *(para + 8);
	double Cr = *(para + 9);

	double rj2000[3], a0[3], ar[3], rs[6];
	double r, tai1, tai2, date1, date2, date;
	int i;

	rj2000[0] = *x;
	rj2000[1] = *(x + 1);
	rj2000[2] = *(x + 2);
	r = norm(rj2000, 3, 2);
	tai1 = taia1;
	tai2 = taib1 + t / 86400;
	iauTaitt(tai1, tai2, &date1, &date2);

	date = date1 + date2;

	void* ephem;
	ephem = jpl_init_ephemeris(ephemeris_filename, NULL, NULL);
    jpl_pleph(ephem, date, 11, 3, rs, 0);
	for (i = 0; i < 3; i++)
	{
		rs[i] = rs[i] * 149597870700.0;
	}
	jpl_close_ephemeris(ephem);
	R(ar, rj2000, rs, Re, c, Sm, Ls, Cr);
	for (i = 0; i < 3; i++)
	{
		a0[i] = -mu * rj2000[i] / (r * r * r);
	}
	for (i = 0; i < 3; i++)
	{
		dx[i] = x[3 + i];
		dx[3 + i] = a0[i] + ar[i];
	}
	return 1;//一切顺利，就返回1，告诉调用它的函数，计算正常，否则返回0

}

int TBFun4(double t, const double* x, double* dx, const double* para)
{
	double taia1 = *para;
	double taib1 = *(para + 1);
	double taia2 = *(para + 2);
	double taib2 = *(para + 3);
	double mu = *(para + 4);
	double mus = *(para + 5);
	double mum = *(para + 6);

	double rj2000[3], a0[3], at1[3], at2[3], rs[6], rm[6];
	double r, tai1, tai2, date1, date2, date;
	int i;

	rj2000[0] = *x;
	rj2000[1] = *(x + 1);
	rj2000[2] = *(x + 2);
	r = norm(rj2000, 3, 2);
	tai1 = taia1;
	tai2 = taib1 + t / 86400;
	iauTaitt(tai1, tai2, &date1, &date2);

	date = date1 + date2;

	void* ephem;
	ephem = jpl_init_ephemeris(ephemeris_filename, NULL, NULL);
	jpl_pleph(ephem, date, 11, 3, rs, 0);
	for (i = 0; i < 3; i++)
	{
		rs[i] = rs[i] * 149597870700.0;
    }
	jpl_pleph(ephem, date, 10, 3, rm, 0);
	for (i = 0; i < 3; i++)
	{
		rm[i] = rm[i] * 149597870700.0;
	}
	jpl_close_ephemeris(ephem);

	for (i = 0; i < 3; i++)
	{
		a0[i] = -mu * rj2000[i] / (r * r * r);
	}

	T(at1, rj2000, rs, mus); T(at2, rj2000, rm, mum);

	for (i = 0; i < 3; i++)
	{
		dx[i] = x[3 + i];
		dx[3 + i] = a0[i] + at1[i] + at2[i];
	}
	return 1;//一切顺利，就返回1，告诉调用它的函数，计算正常，否则返回0
}

int TBFun5(double t, const double* x, double* dx, const double* para)
{
	double taia1 = *para;
	double taib1 = *(para + 1);
	double taia2 = *(para + 2);
	double taib2 = *(para + 3);
	double mu = *(para + 4);
	double mus = *(para + 5);
	double mum = *(para + 6);
	double Re = *(para + 7);
	double Sm = *(para + 8);
	double Ls = *(para + 9);
	double Cr = *(para + 10);
	double Fa = *(para + 11);
	double F = *(para + 12);
	double Ap = *(para + 13);
	double fe = *(para + 14);
	double Cd = *(para + 15);
	double c = *(para + 16);
	double omegaev = *(para + 17);


	double rj2000[3], v[3], a0[3], a1[3], a2[3] = {0}, rs[6], rm[6];
	double aj[3], ad[3], ar[3], at1[3], at2[3], recf[3], M[9];
	double r, tai1, tai2, date1, date2, date, utc1, utc2, utc;
	int i;

	rj2000[0] = *x;
	rj2000[1] = *(x + 1);
	rj2000[2] = *(x + 2);
	v[0] = *(x + 3);
	v[1] = *(x + 4);
	v[2] = *(x + 5);
	r = norm(rj2000, 3, 2);

	tai1 = taia1;
	tai2 = taib1 + t / 86400;
	iauTaitt(tai1, tai2, &date1, &date2);
	iauTaiutc(tai1, tai2, &utc1, &utc2);
	
	for (i = 0; i < 3; i++)
	{
		a0[i] = -mu * rj2000[i] / (r * r * r);
	}

	J20002ecf(date1, date2, M); matrixmulti(M, rj2000, recf, 2);
	J(recf, Re, mu, a1, a2);
	ecf2J2000(date1, date2, M); matrixmulti(M, a2, aj, 2);

	D(ad, rj2000, v, date1, date2, omegaev, Re, fe, Cd, Sm, Fa, F, Ap);

	date = date1 + date2;
	utc = utc1 + utc2;

	void* ephem;
	ephem = jpl_init_ephemeris(ephemeris_filename, NULL, NULL);
	jpl_pleph(ephem, utc, 11, 3, rs, 0);
	for (i = 0; i < 3; i++)
	{
		rs[i] = rs[i] * 149597870700.0;
	}
    jpl_close_ephemeris(ephem);
    ephem = jpl_init_ephemeris(ephemeris_filename, NULL, NULL);
	jpl_pleph(ephem, utc, 10, 3, rm, 0);
	for (i = 0; i < 3; i++)
	{
		rm[i] = rm[i] * 149597870700.0;
	}
	jpl_close_ephemeris(ephem);

	R(ar, rj2000, rs, Re, c, Sm, Ls, Cr);

	T(at1, rj2000, rs, mus); T(at2, rj2000, rm, mum);

	for (i = 0; i < 3; i++)
	{
		dx[i] = x[3 + i];
		dx[3 + i] = a0[i] + aj[i] + ad[i] + ar[i] + at1[i] + at2[i];
	}
	return 1;//一切顺利，就返回1，告诉调用它的函数，计算正常，否则返回0
}

void TBAll(double* rv, int* t1, int* t2, double fd1, double fd2, double* para,int *numpoint)
{
	double uta1, utb1, uta2, utb2, taia1, taib1, taia2, taib2;
	double t11, t22, t;
	double abstol[6] = { 1e-4,1e-4,1e-4,1e-7,1e-7,1e-7 };
    double reltol = 1e-10;
    int flag;
	double mu = *para;
	double mus = *(para + 1);
	double mum = *(para + 2);
	double Re = *(para + 3);
	double Sm = *(para + 4);
	double Ls = *(para + 5);
	double Cr = *(para + 6);
	double Fa = *(para + 7);
	double F = *(para + 8);
	double Ap = *(para + 9);
	double fe = *(para + 10);
	double Cd = *(para + 11);
	double c = *(para + 12);
	double omegaev = *(para + 13);
	double n = *(para + 14);

	iauCal2jd(*t1, *(t1 + 1), *(t1 + 2), &uta1, &utb1);
	iauCal2jd(*t2, *(t2 + 1), *(t2 + 2), &uta2, &utb2);
	iauUtctai(uta1, utb1 + fd1, &taia1, &taib1);
	iauUtctai(uta2, utb2 + fd2, &taia2, &taib2);

	t11 = (taia1 + taib1) * 86400;
	t22 = (taia2 + taib2) * 86400;
	t = t22 - t11;

    FILE* fid = fopen("temp.txt", "w");
	if (n == 0)
	{
		double para0[1] = {mu};
        flag = ode45(TBFun0, rv, para0, 0, t, 6, *numpoint, abstol, reltol);
	}
	else if (n == 1)
	{
		double para1[6] = { taia1,taib1,taia2,taib2,mu,Re };
        flag = ode45(TBFun1, rv, para1, 0, t, 6, *numpoint, abstol, reltol);
	}
	else if (n == 2)
	{
		double para2[13] = { taia1,taib1,taia2,taib2,mu,omegaev,Re,fe,Cd,Sm,Fa,F,Ap };
        flag = ode45(TBFun2, rv, para2, 0, t, 6, *numpoint, abstol, reltol);
	}
	else if (n == 3)
	{
		double para3[10] = { taia1,taib1,taia2,taib2,mu,Re,c,Sm,Ls,Cr };
        flag = ode45(TBFun3, rv, para3, 0, t, 6, *numpoint, abstol, reltol);
	}
	else if (n == 4)
	{
		double para4[7] = { taia1,taib1,taia2,taib2,mu,mus,mum };
        flag = ode45(TBFun4, rv, para4, 0, t, 6, *numpoint, abstol, reltol);
	}
	else if (n == 5)
	{
		double para5[18] = { taia1,taib1,taia2,taib2,mu,mus,mum,Re,Sm,Ls,Cr,Fa,F,Ap,fe,Cd,c,omegaev };
        flag = ode45(TBFun5, rv, para5, 0, t, 6, *numpoint, abstol, reltol,0,-1,-1,fid);
	}
    fclose(fid);//如果打开了文件，别忘了关
}
