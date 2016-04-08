#include <cstdio>
const int maxn = 10, maxm = 46;
int n, m, e[maxn], sz[1 << maxn], cnt[1 << maxn];
long long c[maxm][maxm], f[1 << maxn][maxm];
double ans;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		e[u] |= 1 << v;
		e[v] |= 1 << u;
	}
	c[0][0] = 1;
	for(int i = 1; i <= m; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	for(int s = 1; s < 1 << n; ++s)
	{
		sz[s] = sz[s >> 1] + (s & 1);
		if(sz[s] == 1)
			continue;
		for(int i = 0; i < n; ++i)
			if((s >> i) & 1)
				cnt[s] += sz[e[i] & s];
		cnt[s] >>= 1;
		int lowbit = s & -s;
		for(int t = (s - 1) & s; t; t = (t - 1) & s)
			if(t & lowbit)
				for(int i = 0; i <= cnt[t]; ++i)
					for(int j = 0, o = s ^ t; j <= cnt[o]; ++j)
						f[s][i + j] += (c[cnt[t]][i] - f[t][i]) * c[cnt[o]][j];
	}
	for(int i = 0, all = (1 << n) - 1; i <= m; ++i)
		ans += (double)f[all][i] / c[cnt[all]][i];
	ans /= m + 1;
	printf("%.6f\n", ans);
	return 0;
}
