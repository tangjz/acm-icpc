#include <cstdio>
const int maxn = 100010;
int t, n;
double p, f[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%lf", &n, &p);
		f[1] = 0.0;
		for(int i = 1; i < n; ++i)
		{
			double pi = 2.0 * (n - i) * i / (n * (n - 1.0)) * p;
			f[i + 1] = f[i] + 1 + (1 - pi) / pi;
		}
		printf("%.3f\n", f[n]);
	}
	return 0;
}
