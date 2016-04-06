#include <cstdio>
#include <cstring>
int n, tm, t[5010];
long double p[5010], f[2][5010], g[5010], ans;
long double pow(long double x, int n)
{
	long double ret = 1.0;
	while(n)
	{
		if(n & 1)
			ret *= x;
		x *= x;
		n >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &tm);
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d%d", &x, &t[i]);
		p[i] = x / 100.0;
	}
	p[n] = 0, t[n] = 5000;
	f[0][0] = 1;
	for(int i = 0; i <= n; ++i)
	{
		int o = i & 1;
		long double pp = pow(1 - p[i], t[i]);
		memset(f[o ^ 1], 0, sizeof f[0]);
		for(int j = 0; j <= tm; ++j)
			g[j] = f[o][j];
		for(int j = 0; j <= tm; ++j)
		{
			f[o][j + 1] += f[o][j] * (1 - p[i]);
			f[o ^ 1][j + 1] += f[o][j] * p[i];
			if(j + t[i] <= tm)
			{
				f[o][j + t[i]] -= g[j] * pp;
				f[o ^ 1][j + t[i]] += g[j] * pp;
			}
		}
		ans += i * f[o][tm];
	}
	printf("%.9f\n", (double)ans);
	return 0;
}
