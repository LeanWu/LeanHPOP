#include"a.h"

void CS(double n, double m, double* Cnm, double* Snm)
{
    if (n == 2)
    {
        if (m == 0)
        {
            *Cnm = -4.8416537488647e-04;
            *Snm = 0;
        }
        else if (m == 1)
        {
            *Cnm = -1.8698764000000e-10;
            *Snm = 1.1952801000000e-09;
        }
        else if (m == 2)
        {
            *Cnm = 2.4392607486563e-06;
            *Snm = -1.4002663975880e-06;
        }
    }
    else if (n == 3)
    {
        if (m == 0)
        {
            *Cnm = 9.5717059088800e-07;
            *Snm = 0;
        }
        else if (m == 1)
        {
            *Cnm = 2.0301372055530e-06;
            *Snm = 2.4813079825561e-07;
        }
        else if (m == 2)
        {
            *Cnm = 9.0470634127291e-07;
            *Snm = -6.1892284647849e-07;
        }
        else if (m == 3)
        {
            *Cnm = 7.2114493982309e-07;
            *Snm = 1.4142039847354e-06;
        }
    }
    else if (n == 4)
    {
        if (m == 0)
        {
            *Cnm = 5.3977706835730e-07;
            *Snm = 0;
        }
        if (m == 1)
        {
            *Cnm = -5.3624355429851e-07;
            *Snm = -4.7377237061597e-07;
        }
        if (m == 2)
        {
            *Cnm = 3.5067015645938e-07;
            *Snm = 6.6257134594268e-07;
        }
        if (m == 3)
        {
            *Cnm = 9.9086890577441e-07;
            *Snm = -2.0098735484731e-07;
        }
        if (m == 4)
        {
            *Cnm = -1.8848136742527e-07;
            *Snm = 3.0884803690355e-07;
        }
    }
}

double P(double n, double m, double u)
{
    double Pnm = 0;

    if (n == 0 && m == 0)
        Pnm = 1;
    else if (n == 1 && m == 0)
        Pnm = sqrt(3) * u;
    else if (n == 1 && m == 1)
        Pnm = sqrt(3) * sqrt(1 - (u * u));
    else
    {
        if (n < m)
            Pnm = 0;
        else if (n == m)
            Pnm = P(n - 1, n - 1, u) * sqrt((2 * n + 1) / (2 * n)) * sqrt(1 - (u * u));
        else
            Pnm = sqrt((2 * n + 1) * (2 * n - 1) / ((n + m) * (n - m))) * u * P(n - 1, m, u) - sqrt((2 * n + 1) * (n - 1 + m) * (n - 1 - m) / ((2 * n - 3) * (n + m) * (n - m))) * P(n - 2, m, u);
    }

    return Pnm;
}

void ecf2sph(double* recf, double* e1, double* e2, double* e3)
{
    double x = 0, y = 0, z = 0;
    x = *recf;
    y = *(recf + 1);
    z = *(recf + 2);

    *e1 = x / sqrt(x * x + y * y + z * z);
    *(e1+1) = y / sqrt(x * x + y * y + z * z);
    *(e1+2) = z / sqrt(x * x + y * y + z * z);

    *e2 = -y / sqrt(x * x + y * y);
    *(e2 + 1) = x / sqrt(x * x + y * y);
    *(e2 + 2) = 0;

    cross(e1, e2, e3);
}

void J(double* recf, double Re, double mu, double* a1, double* a2)
{
    double r = 0, x = 0, y = 0, z = 0, p = 0, q = 0, PI = atan(1.0) * 4, b = 0, c1 = 0, c2 = 0, c3 = 0, c = 0, Cnm = 0, Snm = 0;
    double e1[3] = { 0 }, e2[3] = { 0 }, e3[3] = { 0 };
    double n = 0, m = 0;
    int i = 0;

    r = norm(recf, 3, 2);
    ecf2sph(recf, e1, e2, e3);
    x = *recf;
    y = *(recf + 1);
    z = *(recf + 2);
    p = asin(z / r);
    if (y > 0)
        q = acos(x / sqrt(x * x + y * y));
    else
        q = 2 * PI - acos(x / sqrt(x * x + y * y));

    for (i = 0; i < 3; i++)
    {
        *(a1 + i) = -mu * (*(e1 + i)) / (r * r);
    }
    for (i = 0; i < 3; i++)
    {
        for (n = 2; n <= 4; n++)
        {
            b = exponent(Re / r, n);
            for (m = 0; m <= n; m++)
            {
                CS(n, m, &Cnm, &Snm);
                c1 = (1 + n) * cos(p) * P(n, m, sin(p)) * (Cnm * cos(m * q) + Snm * sin(m * q)) * (*(e1 + i));
                c2 = m * P(n, m, sin(p)) * (Cnm * sin(m * q) - Snm * cos(m * q)) * (*(e2 + i));
                c3 = (n * sin(p) * P(n, m, sin(p)) - sqrt((2 * n + 1) * (n + m) * (n - m) / (2 * n - 1)) * P(n - 1, m, sin(p))) * (Cnm * cos(m * q) + Snm * sin(m * q)) * (*(e3 + i));
                c = c1 + c2 + c3;
                *(a2 + i) = *(a2 + i) - mu * b * c / (r * r * cos(p));
            }
        }
    }

}

void D(double* ad, double* r, double* v, double date1, double date2, double omegaev, double Re, double fe, double Cd, double Sm, double Fa, double F, double Ap)
{
    double omegaeecf[3] = { 0,0,omegaev }, omegaej2000[3] = { 0 };
    double R[9] = { 0 }, vea[3] = { 0 }, ve[3] = { 0 }, ve0 = 0, recf[3] = { 0 };
    double g_long = 0, g_phi = 0, h = 0, tai1, tai2, utc1, utc2, utc01, utc02, fd, rho;
    int i, y, m, d;

    ecf2J2000(date1, date2, R);	matrixmulti(R, omegaeecf, omegaej2000, 2); cross(omegaej2000, r, vea);
    for (i = 0; i < 3; i++)
    {
        ve[i] = v[i] - vea[i];
    }
    ve0 = norm(ve, 3, 2);

    J20002ecf(date1, date2, R);	matrixmulti(R, r, recf, 2);
    iauGc2gd(1, recf, &g_long, &g_phi, &h);

    iauTttai(date1, date2, &tai1, &tai2); iauTaiutc(tai1, tai2, &utc1, &utc2);
    iauJd2cal(utc1, utc2, &y, &m, &d, &fd); iauCal2jd(y, 1, 1, &utc01, &utc02);

    struct nrlmsise_output output;
    struct nrlmsise_input input;
    struct nrlmsise_flags flags;
    struct ap_array aph;

    input.doy = ceil(utc2 - utc02);
    input.year = y;
    input.sec = fd * 86400;
    input.alt = h * 1e-3;
    input.g_lat = g_phi * 180 / acos(-1.0);
    input.g_long = g_long * 180 / acos(-1.0);
    input.lst = input.sec / 3600 + input.g_long / 15;
    input.f107A = Fa;
    input.f107 = F;
    input.ap = Ap;

    for (i = 0; i < 7; i++)
        aph.a[i] = input.ap;

    for (i = 0; i < 24; i++)
        flags.switches[i] = 1;

    gtd7(&input, &flags, &output);
    rho = output.d[5];
    for (i = 0; i < 3; i++)
    {
        *(ad + i) = -0.5 * Cd * Sm * rho * ve0 * ve[i];
    }
}

void R(double* ar, double* r, double* rs, double Re, double c, double Sm, double Ls, double Cr)
{
    double x = rs[0], y = rs[1], z = rs[2], phi;
    double rs0 = norm(rs, 3, 2);
    double theta = acos(z / rs0);
    if (y > 0)
    {
        phi = acos(x / (rs0 * sin(theta)));
    }
    else
    {
        phi = 2 * acos(-1.0) - acos(x / (rs0 * sin(theta)));
    }
    double P[9], A1[9], A2[9];
    A(3, phi, A1); A(2, theta, A2);
    matrixmulti(A1, A2, P, 1);
    matrixtrans(P);

    double rscr[3], rcr[3];
    matrixmulti(P, rs, rscr, 2); matrixmulti(P, r, rcr, 2);
    double x0 = rcr[0], y0 = rcr[1], z0 = rcr[2];
    int K;
    if ((x0 * x0 + y0 * y0 < Re * Re) && (z0 * rscr[2] < 0))
        K = 0;
    else
        K = 1;

    double rm[3];
    for (int i = 0; i < 3; i++)
    {
        rm[i] = r[i] - rs[i];
    }
    double rm0 = norm(rm, 3, 2);
    for (int i = 0; i < 3; i++)
    {
        ar[i] = K * Cr * Sm * Ls * rm[i] / (4 * acos(-1.0) * c * rm0 * rm0 * rm0);
    }
}

void T(double* at, double* r, double* rs, double mus)
{
    double rm[3], rm0, rs0;
    for (int i = 0; i < 3; i++)
    {
        rm[i] = r[i] - rs[i];
    }
    rm0 = norm(rm, 3, 2);
    rs0 = norm(rs, 3, 2);
    for (int i = 0; i < 3; i++)
    {
        at[i] = -mus * (rm[i] / (rm0 * rm0 * rm0) + rs[i] / (rs0 * rs0 * rs0));
    }
}