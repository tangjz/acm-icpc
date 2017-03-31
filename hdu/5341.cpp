#include <stdio.h>
#include <algorithm>
const int maxn = 10000001;
int tot, pr[maxn >> 3 | 1], d[maxn], f[maxn], g[maxn];
int pk[maxn], ot[maxn], s[maxn];
inline int sqr(int x)
{
	return x * x;
}
int main()
{
	f[1] = g[1] = pk[1] = ot[1] = s[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = i;
			f[i] = 1 - i;
			g[i] = (i << 1) - 1;
			pk[i] = i;
			ot[i] = 1;
			s[i] = i << 1;
		}
		for(int j = 0, k = (maxn - 1) / i; pr[j] <= k; ++j)
		{
			int o = i * pr[j];
			d[o] = pr[j];
			if(d[i] == pr[j])
			{
				pk[o] = pk[i] * pr[j];
				ot[o] = ot[i];
				s[o] = s[i] * pr[j] + pk[o];
				f[o] = f[i];
				g[o] = g[ot[o]] * (s[o] - s[i]);
				break;
			}
			else
			{
				pk[o] = pr[j];
				ot[o] = i;
				s[o] = s[pr[j]];
				f[o] = f[i] * f[pr[j]];
				g[o] = g[i] * g[pr[j]];
			}
		}
	}
	for(int i = 1; i < maxn; ++i)
	{
		f[i] = f[i - 1] + i * f[i];
		g[i] = g[i - 1] + (g[i] << 1) - i;
	}
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int n, ans = 0;
		scanf("%d", &n);
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			ans += (f[j] - f[i - 1]) * sqr(g[n / i]);
		}
		printf("%u\n", ans);
	}
	return 0;
}
