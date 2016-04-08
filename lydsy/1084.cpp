#include <cstdio>
const int maxn = 101, maxk = 11;
int n, m, k, a[3][maxn], f[maxn][maxn][maxk];
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			scanf("%d", &a[j][i]);
			a[j][i] += a[j][i - 1];
		}
	if(m == 1)
	{
		for(int i = 1; i <= n; ++i)
			for(int t = 1; t <= k; ++t)
			{
				f[0][i][t] = f[0][i - 1][t];
				for(int j = 0; j < i; ++j)
					upd(f[0][i][t], f[0][j][t - 1] + a[1][i] - a[1][j]);
			}
		printf("%d\n", f[0][n][k]);
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			for(int t = 1; t <= k; ++t)
			{
				f[i][j][t] = f[i - 1][j][t];
				upd(f[i][j][t], f[i][j - 1][t]);
				for(int p = 0; p < i; ++p)
					upd(f[i][j][t], f[p][j][t - 1] + a[1][i] - a[1][p]);
				for(int p = 0; p < j; ++p)
					upd(f[i][j][t], f[i][p][t - 1] + a[2][j] - a[2][p]);
				if(i == j)
					for(int p = 0; p < i; ++p)
						upd(f[i][j][t], f[p][p][t - 1] + a[1][i] - a[1][p] + a[2][j] - a[2][p]);
			}
	printf("%d\n", f[n][n][k]);
	return 0;
}
