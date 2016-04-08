/*
ID: tangjin2
LANG: C++
TASK: nocows
*/
#include <cstdio>
const int maxn = 201, mod = 9901;
int n, m, f[maxn][maxn], g[maxn][maxn];
int main()
{
	freopen("nocows.in", "r", stdin);
	freopen("nocows.out", "w", stdout);
	scanf("%d%d", &n, &m);
	f[1][1] = g[1][1] = 1;
	for(int i = 2; i <= m; ++i)
	{
		for(int j = 3; j <= n; ++j)
			for(int k = 1; k < j; k += 2)
				f[i][j] = (f[i][j] + f[i - 1][k] * g[i - 1][j - 1 - k] + g[i - 2][k] * f[i - 1][j - 1 - k]) % mod;
		for(int j = 1; j <= n; ++j)
		{
			g[i][j] = g[i - 1][j] + f[i][j];
			if(g[i][j] >= mod)
				g[i][j] -= mod;
		}
	}
	printf("%d\n", f[m][n]);
	return 0;
}
