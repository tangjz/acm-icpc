#include <cmath>
#include <cstdio>
const int maxn = 100010;
int n;
double pw, vw[maxn], pf[maxn], vf[maxn], th[maxn];
template<class T> const T& max(const T& x, const T& y)
{
	return x < y ? y : x;
}
double cost(double lim)
{
	double res = pw * lim;
	for(int i = 0; i < n; ++i)
		res += max(0.0, th[i] - vw[i] * lim) / vf[i] * pf[i];
	return res;
}
int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		scanf("%lf", &pw);
		for(int i = 0; i < n; ++i)
			scanf("%lf%lf%lf%lf", vw + i, pf + i, vf + i, th + i);
		double L = 0, R = 1e3;
		for(int i = 0; i < 233; ++i)
		{
			double ML = L + (R - L) / 3, MR = R - (R - L) / 3;
			if(cost(ML) < cost(MR))
				R = MR;
			else
				L = ML;
		}
		printf("%.8f\n", cost(L));
	}
}
