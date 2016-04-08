#include <cstdio>
#include <cstring>
const int maxn = 101;
int n, m, e[maxn][maxn];
double f[maxn][maxn];
int main()
{
	scanf("%d%d", &n, &m);
	memset(e, 0x3f, sizeof e);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(e[u][v] > w)
		{
			e[u][v] = e[v][u] = w;
			f[u][v] = f[v][u] = 1;
		}
	}
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
		{
			if(i == k)
				continue;
			for(int j = 1; j <= n; ++j)
			{
				if(i == j || j == k || e[i][j] < e[i][k] + e[k][j])
					continue;
				if(e[i][j] > e[i][k] + e[k][j])
				{
					e[i][j] = e[i][k] + e[k][j];
					f[i][j] = 0;
				}
				f[i][j] += f[i][k] * f[k][j];
			}
		}
	for(int k = 1; k <= n; ++k)
	{
		double ret = 0;
		for(int i = 1; i <= n; ++i)
		{
			if(i == k)
				continue;
			for(int j = 1; j <= n; ++j)
			{
				if(i == j || j == k || e[i][j] != e[i][k] + e[k][j])
					continue;
				ret += f[i][k] * f[k][j] / f[i][j];
			}
		}
		printf("%.3f\n", ret);
	}
	return 0;
}
