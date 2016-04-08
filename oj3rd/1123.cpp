#include <cstdio>
const int maxn = 101;
int n, m, a[maxn][maxn], f[maxn][maxn], p[maxn][maxn], ans[maxn];
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				scanf("%d", &a[i][j]);
				f[i][j] = ~0u >> 1;
				if(j > 1 && f[i][j] > f[i - 1][j - 1])
					f[i][j] = f[i - 1][j - 1];
				if(f[i][j] > f[i - 1][j])
					f[i][j] = f[i - 1][j];
				if(j < m && f[i][j] > f[i - 1][j + 1])
					f[i][j] = f[i - 1][j + 1];
				f[i][j] += a[i][j];
			}
		int tmp = m;
		for(int i = 1; i < m; ++i)
			if(f[n][tmp] > f[n][i])
				tmp = i;
		for(int i = 1; i <= m; ++i)
			p[n][i] = f[n][tmp] == f[n][i];
		for(int i = n - 1; i >= 1; --i)
			for(int j = m; j >= 1; --j)
			{
				p[i][j] = 0;
				if(j > 1 && p[i + 1][j - 1] && f[i][j] + a[i + 1][j - 1] == f[i + 1][j - 1])
					p[i][j] = j - 1;
				if(p[i + 1][j] && f[i][j] + a[i + 1][j] == f[i + 1][j])
					p[i][j] = j;
				if(j < m && p[i + 1][j + 1] && f[i][j] + a[i + 1][j + 1] == f[i + 1][j + 1])
					p[i][j] = j + 1;
			}
		for(int i = 1; i <= m; ++i)
			if(p[1][i])
				ans[1] = i;
		for(int i = 2; i <= n; ++i)
			ans[i] = p[i - 1][ans[i - 1]];
		for(int i = 1; i <= n; ++i)
			printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
