#include <stdio.h>
#include <cstring>
const int maxn = 301;
int t, n, m, a[maxn], f[maxn][maxn], g[maxn][maxn];
inline void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			memset(f[i] + i, 0, (n - i + 1) * sizeof(int));
			memset(g[i] + i, 0, (n - i + 1) * sizeof(int));
		}
		for(int i = 1, x; i <= m; ++i)
		{
			scanf("%d", &x);
			for(int j = 1; j <= n; ++j)
				for(int k = j + 1; k <= n; ++k)
					f[j][k] |= a[k] - a[j] == x;
		}
		for(int l = 2; l <= n; ++l)
			for(int i = 1, j = l; j <= n; ++i, ++j)
			{
				upd(g[i][j], g[i + 1][j]);
				upd(g[i][j], g[i][j - 1]);
				if(f[i][j] && g[i + 1][j - 1] == j - i - 1)
					upd(g[i][j], j - i + 1);
				for(int k = i + 1; k < j; ++k)
				{
					upd(g[i][j], g[i][k] + g[k + 1][j]);
					bool flag1 = f[i][k] && g[i + 1][k - 1] == k - i - 1;
					bool flag2 = f[k][j] && g[k + 1][j - 1] == j - k - 1;
					if(flag1)
						upd(g[i][j], g[i + 1][k - 1] + 2 + g[k + 1][j]);
					if(flag2)
						upd(g[i][j], g[i][k - 1] + 2 + g[k + 1][j - 1]);
					if(flag1 && flag2 && a[k] - a[i] == a[j] - a[k])
						upd(g[i][j], j - i + 1);
				}
			}
		printf("%d\n", g[1][n]);
	}
	return 0;
}
