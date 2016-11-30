#include <cstdio>
const int maxn = 10001;
const double eps = 1e-9;
int t, n, a[maxn], b[maxn], c[maxn];
double maxf(double x)
{
	double f = (a[0] * x + b[0]) * x + c[0], g;
	for(int i = 1; i < n; ++i)
	{
		g = (a[i] * x + b[i]) * x + c[i];
		if(f < g)
			f = g;
	}
	return f;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d%d", a + i, b + i, c + i);
		double l = 0, r = 1000, ml, mr;
		while(r - l >= eps)
		{
			ml = l + (r - l) / 3;
			mr = r - (r - l) / 3;
			if(maxf(ml) < maxf(mr))
				r = mr;
			else
				l = ml;
		}
		printf("%.4f\n", maxf(l));
	}
	return 0;
}
