#include"ODE45.h"

double eps(double t)
{
	if (t == 0)
		return pow(2.0, -1074.0);
	else
		return pow(2.0, -52.0 + floor(log(fabs(t)) / log(2.0)));
}

//求叉乘
void cross(double* a1, double* a2, double* a)
{
	*a = (*(a1 + 1)) * (*(a2 + 2)) - (*(a1 + 2)) * (*(a2 + 1));
	*(a + 1) = (*(a1 + 2)) * (*a2) - (*a1) * (*(a2 + 2));
	*(a + 2) = (*(a2 + 1)) * (*a1) - (*a2) * (*(a1 + 1));
}

//求乘方
double exponent(double x, int n)
{
	int i = 0;
	double ans = x;
	for (i = 1; i < n; i++)
	{
		ans = ans * x;
	}
	return ans;
}

//求矩阵相乘
void matrixmulti(double* R1, double* R2, double* R,int type)
{
	if (type == 1)
	{
		*(R + 0) = (*(R1 + 0)) * (*(R2 + 0)) + (*(R1 + 1)) * (*(R2 + 3)) + (*(R1 + 2)) * (*(R2 + 6));
		*(R + 1) = (*(R1 + 0)) * (*(R2 + 1)) + (*(R1 + 1)) * (*(R2 + 4)) + (*(R1 + 2)) * (*(R2 + 7));
		*(R + 2) = (*(R1 + 0)) * (*(R2 + 2)) + (*(R1 + 1)) * (*(R2 + 5)) + (*(R1 + 2)) * (*(R2 + 8));
		*(R + 3) = (*(R1 + 3)) * (*(R2 + 0)) + (*(R1 + 4)) * (*(R2 + 3)) + (*(R1 + 5)) * (*(R2 + 6));
		*(R + 4) = (*(R1 + 3)) * (*(R2 + 1)) + (*(R1 + 4)) * (*(R2 + 4)) + (*(R1 + 5)) * (*(R2 + 7));
		*(R + 5) = (*(R1 + 3)) * (*(R2 + 2)) + (*(R1 + 4)) * (*(R2 + 5)) + (*(R1 + 5)) * (*(R2 + 8));
		*(R + 6) = (*(R1 + 6)) * (*(R2 + 0)) + (*(R1 + 7)) * (*(R2 + 3)) + (*(R1 + 8)) * (*(R2 + 6));
		*(R + 7) = (*(R1 + 6)) * (*(R2 + 1)) + (*(R1 + 7)) * (*(R2 + 4)) + (*(R1 + 8)) * (*(R2 + 7));
		*(R + 8) = (*(R1 + 6)) * (*(R2 + 2)) + (*(R1 + 7)) * (*(R2 + 5)) + (*(R1 + 8)) * (*(R2 + 8));
	}
	else
	{
		*(R + 0) = (*(R1 + 0)) * (*(R2 + 0)) + (*(R1 + 1)) * (*(R2 + 1)) + (*(R1 + 2)) * (*(R2 + 2));
		*(R + 1) = (*(R1 + 3)) * (*(R2 + 0)) + (*(R1 + 4)) * (*(R2 + 1)) + (*(R1 + 5)) * (*(R2 + 2));
		*(R + 2) = (*(R1 + 6)) * (*(R2 + 0)) + (*(R1 + 7)) * (*(R2 + 1)) + (*(R1 + 8)) * (*(R2 + 2));
	}
}

//求矩阵转置
void matrixtrans(double* R)
{
	double R1[9];
	int i;
	for (i = 0; i < 9; i++)
	{
		R1[i] = R[i];
	}
	R[1] = R1[3]; R[2] = R1[6]; R[5] = R1[7];
	R[3] = R1[1]; R[6] = R1[2]; R[7] = R1[5];
}

//求1,2,inf-范数
double norm(const double* vec, int n, int type)
{
	int i;
	double res = 0.0;
	if (type == 1)
	{
		for (i = 0; i < n; i++)
		{
			if (vec[i] >= 0)
				res += vec[i];
			else
				res -= vec[i];
		}
	}
	else if (type == 2)
	{
		for (i = 0; i < n; i++)
			res += vec[i] * vec[i];
		res = sqrt(res);
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			if (vec[i] >= 0.0)
			{
				if (vec[i] > res)
					res = vec[i];
			}
			else
			{
				if (-vec[i] > res)
					res = -vec[i];
			}
		}
	}
	return res;
}

int ode45(int (*fun)(double t, const double* x, double* dx, const double* para), double* x, const double* para,
	double t0, double tf, int n, int& NumPoint, const double* AbsTol, double RelTol,
	int NormControl, double MaxStep, double InitialStep, FILE* fid)
{
	// Stats
	int flag = 0, odeflag = 0;
	int nsteps, nfailed, nfevals, tdir, nofailed;
	double rtol, normx, t, powth, hmax, hmin, absh, rh, h, tnew, normxnew, errwt, err, temp;
	int i, j, k;
	double* work[10];
	for (i = 0; i < 10; i++)
		work[i] = new double[n];
	for (i = 0; i < 10; i++)
		for (j = 0; j < n; j++)
			work[i][j] = 0.0;
	double* threshold = work[7];
	double* xnew = work[9];
	double hB[7][6];
	nsteps = 0;
	nfailed = 0;
	nfevals = 0;

	// Handle solver arguments
	tdir = sign(tf - t0);
	flag = fun(t0, x, work[0], para);
	if (flag < 1)
	{
		odeflag = 0;
		goto Final;
	}
	{
		rtol = RelTol;
		if (rtol < 100.0 * eps(1.0))
			rtol = 100.0 * eps(1.0);
		normx = 0.0;
		threshold[0] = AbsTol[0] / rtol;
		if (NormControl)
			normx = norm(x, n, 2);
		else
			for (i = 1; i < n; i++)
				threshold[i] = AbsTol[i] / rtol;
		if (MaxStep > 0.0)
			hmax = min(fabs(tf - t0), MaxStep);
		else
			hmax = min(fabs(tf - t0), fabs(0.1 * (tf - t0)));

		nfevals = nfevals + 1;

		t = t0;
		// Allocate memory if we're generating output.
		// alloc in chunks
		NumPoint = 1;
		if (fid)
		{
			fprintf(fid, "%22.14e", t);
			for (i = 0; i < n; i++)
				fprintf(fid, "%24.14e", x[i]);
			fflush(fid);
		}

		// Initialize method parameters.
		powth = 1.0 / 5.0;
		static const double A[6] = { 1.0 / 5.0, 3.0 / 10.0, 4.0 / 5.0, 8.0 / 9.0, 1.0, 1.0 };
		static const double B[7][6] =
		{ {1.0 / 5.0,	3.0 / 40.0,	44.0 / 45.0,	19372.0 / 6561.0,		9017.0 / 3168.0,		35.0 / 384.0		},
			{0.0,		9.0 / 40.0,	-56.0 / 15.0,	-25360.0 / 2187.0,	-355.0 / 33.0,		0.0				},
			{0.0,		0.0,		32.0 / 9.0,	64448.0 / 6561.0,		46732.0 / 5247.0,		500.0 / 1113.0	},
			{0.0,		0.0,		0.0,		-212.0 / 729.0,		49.0 / 176.0,			125.0 / 192.0		},
			{0.0,		0.0,		0.0,		0.0,				-5103.0 / 18656.0,	-2187.0 / 6784.0	},
			{0.0,		0.0,		0.0,		0.0,				0.0,				11.0 / 84.0		},
			{0.0,		0.0,		0.0,		0.0,				0.0,				0.0				} };
		static const double E[7] = { 71.0 / 57600.0, 0.0, -71.0 / 16695.0, 71.0 / 1920.0, -17253.0 / 339200.0, 22.0 / 525.0, -1.0 / 40.0 };
		hmin = 16.0 * eps(t);
		if (InitialStep <= 0.0)
		{
			// Compute an initial step size h using y'(t).
			absh = min(hmax, fabs(tf - t0));
			if (NormControl)
				rh = (norm(work[0], n, 2) / max(normx, threshold[0])) / (0.8 * pow(rtol, powth));
			else
			{
				for (i = 0; i < n; i++)
					xnew[i] = work[0][i] / max(fabs(x[i]), threshold[i]);
				rh = norm(xnew, n, 3) / (0.8 * pow(rtol, powth));
			}
			if (absh * rh > 1.0)
				absh = 1.0 / rh;
			absh = max(absh, hmin);
		}
		else
			absh = min(hmax, max(hmin, InitialStep));

		// THE MAIN LOOP
		int done = 0;
		while (!done)
		{
			// By default, hmin is a small number such that t+hmin is only slightly
			// different than t.  It might be 0 if t is 0.
			hmin = 16.0 * eps(t);
			absh = min(hmax, max(hmin, absh));    // couldn't limit absh until new hmin
			h = tdir * absh;

			// Stretch the step if within 10// of tf-t.
			if (1.1 * absh >= fabs(tf - t))
			{
				h = tf - t;
				absh = fabs(h);
				done = 1;
			}

			// LOOP FOR ADVANCING ONE STEP.
			nofailed = 1;                      // no failed attempts
			while (1)
			{
				for (i = 0; i < 7; i++)
					for (j = i; j < 6; j++)
						hB[i][j] = h * B[i][j];
				for (k = 0; k < 5; k++)
				{
					for (i = 0; i < n; i++)
					{
						work[8][i] = x[i];
						for (j = 0; j <= k; j++) work[8][i] += work[j][i] * hB[j][k];
					}
					flag = fun(t + h * A[k], work[8], work[k + 1], para);
					if (flag < 1) { odeflag = 0; goto Final; }
				}
				//f(:,2) = feval(fun,t+h*A(1),y+f*hB(:,1),para);
				//f(:,3) = feval(fun,t+h*A(2),y+f*hB(:,2),para);
				//f(:,4) = feval(fun,t+h*A(3),y+f*hB(:,3),para);
				//f(:,5) = feval(fun,t+h*A(4),y+f*hB(:,4),para);
				//f(:,6) = feval(fun,t+h*A(5),y+f*hB(:,5),para);

				tnew = t + h * A[5];
				if (done)
					tnew = tf;   // Hit end point exactly.
				//h = tnew - t;      // Purify h.

				for (i = 0; i < n; i++)
				{
					xnew[i] = x[i];
					for (j = 0; j <= 5; j++) xnew[i] += work[j][i] * hB[j][5];
				}
				flag = fun(tnew, xnew, work[6], para);
				if (flag < 1) { odeflag = 0; goto Final; }

				nfevals = nfevals + 6;

				// Estimate the error.
				for (i = 0; i < n; i++)
				{
					work[8][i] = 0.0;
					for (j = 0; j < 7; j++) work[8][i] += work[j][i] * E[j];
				}
				if (NormControl)
				{
					normxnew = norm(xnew, n, 2);
					errwt = max(max(normx, normxnew), threshold[0]);
					err = absh * (norm(work[8], n, 2) / errwt);
				}
				else
				{
					for (i = 0; i < n; i++)
						work[8][i] /= max(max(fabs(x[i]), fabs(xnew[i])), threshold[i]);
					err = absh * norm(work[8], n, 3);
				}

				// Accept the solution only if the weighted error is no more than the
				// tolerance rtol.  Estimate an h that will yield an error of rtol on
				// the next step or the next try at taking this step, as the case may be,
				// and use 0.8 of this value to avoid failures.
				if (err > rtol)                      // Failed step
				{
					nfailed = nfailed + 1;
					if (absh <= hmin)
					{
						printf("Failure at t=%e.,...Unable to meet integration tolerances without reducing the step size below the smallest value allowed (%e) at time t.", t, hmin);
						odeflag = 0;
						goto Final;
					}

					if (nofailed)
					{
						nofailed = false;
						absh = max(hmin, absh * max(0.1, 0.8 * pow(rtol / err, powth)));
					}
					else
						absh = max(hmin, 0.5 * absh);
					h = tdir * absh;
					done = false;
				}
				else        // Successful step
					break;

			}

			nsteps = nsteps + 1;

			NumPoint = NumPoint + 1;
			if (fid)
			{
				fprintf(fid, "\n");
				fprintf(fid, "%22.14e", tnew);
				for (i = 0; i < n; i++)
					fprintf(fid, "%24.14e", xnew[i]);
				fflush(fid);
			}

			if (done)
				break;


			// If there were no failures compute a new h.
			if (nofailed)
			{
				// Note that absh may shrink by 0.8, and that err may be 0.
				temp = 1.25 * pow(err / rtol, powth);
				if (temp > 0.2)
					absh = absh / temp;
				else
					absh = 5.0 * absh;
			}

			// Advance the integration one step.
			t = tnew;
			for (i = 0; i < n; i++) x[i] = xnew[i];
			if (NormControl)
				normx = normxnew;
			for (i = 0; i < n; i++) work[0][i] = work[6][i];  // Already have f(tnew,ynew)
		}
		for (i = 0; i < n; i++) x[i] = xnew[i];
		odeflag = 1;
	}
Final:
	for (i = 0; i < 10; i++)
		delete[] work[i];
	return odeflag;
}