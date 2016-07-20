#include <cstdio>
#include <cstring>
const int maxn = 101, maxt = 11;
int n, m, s, t, e[maxn][maxn];
long long f[maxt][maxn];
int main()
{
	while(scanf("%d%d%d%d", &n, &m, &s, &t) == 4)
	{
		for(int i = 0; i < n; ++i)
			e[i][0] = 0;
		while(m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u][++e[u][0]] = v;
			e[v][++e[v][0]] = u;
		}
		memset(f[0], 0, n * sizeof(long long));
		f[0][s] = 1;
		for(int i = 0; i < t; ++i)
		{
			memset(f[i + 1], 0, n * sizeof(long long));
			for(int j = 0; j < n; ++j)
				for(int it = 1; it <= e[j][0]; ++it)
				{
					int k = e[j][it];
					f[i + 1][k] += f[i][j];
				}
		}
		long long ans = 0;
		for(int i = 0; i < n; ++i)
			ans += f[t][i];
		printf("%lld\n", ans);
	}
	return 0;
}
