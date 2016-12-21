#include <stdio.h>
const int maxn = 20001, maxl = 14, maxm = (maxl >> 1) + 1, INF = 0x3f3f3f3f, maxs = 40;
int w[maxm], f[maxm][maxn], g[maxm][maxn], t, n, m, k, sz, out[maxs];
int main()
{
	w[0] = 1;
	for(int i = 1; i < maxm; ++i)
		w[i] = w[i - 1] * (maxl - i + 1) / i;
	for(int i = 0; i < maxm; ++i)
		for(int j = 0; j < maxn; ++j)
		{
			if(!i && !j)
				continue;
			f[i][j] = g[i][j] = INF;
			if(i > 0 && f[i][j] > f[i - 1][j])
			{
				f[i][j] = f[i - 1][j];
				g[i][j] = 0;
			}
			if(j >= w[i] && f[i][j] > f[i][j - w[i]] + 1)
			{
				f[i][j] = f[i][j - w[i]] + 1;
				g[i][j] = g[i][j - w[i]] + 1;
			}
		}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d", &n, &m, &k);
		sz = 0;
		for(int i = 0; i < maxl; ++i)
			out[sz++] = 1;
		for(int i = maxm - 1, j = k; i >= 0; j -= w[i] * g[i][j], --i)
			for(int k = 0; k < g[i][j]; ++k)
				out[sz++] = n - i;
		printf("Case #%d: %d\n", Case, sz);
		for(int i = 0; i < sz; ++i)
			printf("%d%c", out[i], " \n"[i == sz - 1]);
	}
	return 0;
}
