#include <cmath>
#include <cstdio>
int K;
double W, D, A, p[10][2], q[10][2], L, R, M;
double F(double x)
{
	double a = 0, b = 0, c = 0, d = 0, pp, qq;
	for(int i = K; i >= 0; --i)
	{
		a = a * x + p[i][0];
		b = b * x + p[i][1];
		c = c * x + q[i][0];
		d = d * x + q[i][1];
	}
	pp = a / b > M ? a / b : M;
	qq = c / d > M ? c / d : M;
	return pp - qq;
}
double simpson(double l, double r)
{
	double m = l + (r - l) / 2;
	return (F(l) + 4 * F(m) + F(r)) * (r - l) / 6;
}
double asr(double l, double r, double eps, double area)
{
	double m = l + (r - l) / 2;
	double la = simpson(l, m), ra = simpson(m, r);
	if(fabs(la + ra - area) <= 15 * eps)
		return la + ra + (la + ra - area) / 15;
	return asr(l, m, eps / 2, la) + asr(m, r, eps / 2, ra);
}
int main()
{
	while(scanf("%lf%lf%lf%d", &W, &D, &A, &K) == 4)
	{
		for(int i = 0; i <= K; ++i)
			scanf("%lf", &p[i][0]);
		for(int i = 0; i <= K; ++i)
			scanf("%lf", &p[i][1]);
		for(int i = 0; i <= K; ++i)
			scanf("%lf", &q[i][0]);
		for(int i = 0; i <= K; ++i)
			scanf("%lf", &q[i][1]);
		L = -D, R = 0;
		while(R - L >= 1e-8)
		{
			M = L + (R - L) / 2;
			if(asr(0, W, 1e-5, simpson(0, W)) < A)
				R = M;
			else
				L = M;
		}
		printf("%.5f\n", -L);
	}
	return 0;
}
