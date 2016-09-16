#include <cstdio>
const int maxn = 20;
const double eps = 1e-8;
int n, k, all, sz[1 << maxn];
double p[maxn], f[1 << maxn], ans[maxn];
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; ++i)
		scanf("%lf", p + i);
	all = (1 << n) - 1;
	f[0] = 1;
	for(int i = 1; i <= all; ++i)
	{
		double cnt = 0;
		for(int j = 0; j < n; ++j)
			if(i & (1 << j))
				cnt += p[j];
		if(1 - cnt < eps)
			f[i] = 0;
		else
		{
			for(int j = 0; j < n; ++j)
				if(i & (1 << j))
					f[i] += f[i ^ (1 << j)] * p[j];
			f[i] /= 1 - cnt;
		}
		sz[i] = sz[i >> 1] + (i & 1);
		if(sz[i] >= k)
			for(int j = 0; j < n; ++j)
				if(~i & (1 << j))
					ans[j] += f[i] * p[j];
	}
	for(int i = 0; i < n; ++i)
		printf("%.10f%c", p[i] < eps ? 0 : 1 - ans[i], " \n"[i == n - 1]);
	return 0;
}
