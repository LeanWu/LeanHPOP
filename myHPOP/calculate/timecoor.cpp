#include"timecoor.h"

void tran(double* R)
{
    double T[9] = { 0 };
    int i = 0;
    *(T + 0) = *(R + 0);
    *(T + 1) = *(R + 3);
    *(T + 2) = *(R + 6);
    *(T + 3) = *(R + 1);
    *(T + 4) = *(R + 4);
    *(T + 5) = *(R + 7);
    *(T + 6) = *(R + 2);
    *(T + 7) = *(R + 5);
    *(T + 8) = *(R + 8);
    for (i = 0; i < 9; i++)
        *(R + i) = *(T + i);
}

void A(int n, double x, double* R)
{
    if (n == 1)
    {
        *R = 1;
        *(R + 1) = 0;
        *(R + 2) = 0;
        *(R + 3) = 0;
        *(R + 4) = cos(x);
        *(R + 5) = -sin(x);
        *(R + 6) = 0;
        *(R + 7) = sin(x);
        *(R + 8) = cos(x);
    }
    else if (n == 3)
    {
        *R = cos(x);
        *(R + 1) = -sin(x);
        *(R + 2) = 0;
        *(R + 3) = sin(x);
        *(R + 4) = cos(x);
        *(R + 5) = 0;
        *(R + 6) = 0;
        *(R + 7) = 0;
        *(R + 8) = 1;
    }
    else
    {
        *R = cos(x);
        *(R + 1) = 0;
        *(R + 2) = sin(x);
        *(R + 3) = 0;
        *(R + 4) = 1;
        *(R + 5) = 0;
        *(R + 6) = -sin(x);
        *(R + 7) = 0;
        *(R + 8) = cos(x);
    }
}

void J20002ecf(double date11, double date12, double* R)
{
    double date01, date02,tai1,tai2,uta,utb,zeta,z,theta, dpsi, deps, eps0,thetag;
    double R1[9],R2[9],R3[9],A1[9], A2[9], A3[9],T[9];

    iauCal2jd(2000, 1, 1, &date01, &date02);
    date02 = date02 + 0.5;
    iauPrec76(date01, date02, date11, date12, &zeta, &z, &theta);
    A(3, z, A1); A(2, -theta, A2); A(3, zeta, A3);
    matrixmulti(A1, A2, T, 1); matrixmulti(T, A3, R1, 1);

    iauNut80(date11, date12, &dpsi, &deps);
    eps0 = iauObl80(date11, date12);
    A(1, deps + eps0, A1); A(3, dpsi, A2); A(1, -eps0, A3);
    matrixmulti(A1, A2, T, 1); matrixmulti(T, A3, R2, 1);

    iauTttai(date11,date12,&tai1,&tai2);
    iauTaiutc(tai1, tai2, &uta, &utb);
    thetag = iauGst94(uta, utb);
    A(3, -thetag, R3);

    matrixmulti(R3, R2, T, 1); matrixmulti(T, R1, R, 1);
}

void ecf2J2000(double date11, double date12, double* R)
{
    J20002ecf(date11, date12, R);
    tran(R);
}