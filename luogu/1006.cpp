#include <cstdio>
int n, m, num[51][51], f[101][51][51];
int main()
{
	int i, j, k, x1, x2, y1, y2, tmp;
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= m; ++j) scanf("%d", &num[i][j]);
	for(k = 1;k <= n + m - 2; ++k)
		for(x1 = 1; x1 <= n; ++x1)
			for(x2 = 1; x2 <= n; ++x2)
			{
				if(x1 == x2 || x1 - 1 > k|| x2 - 1 > k) continue;
				y1 = k - x1 + 2;
				y2 = k - x2 + 2;
				if(y1 > m || y2 > m) continue;
				if(y1 > 1 && y2 > 1 && f[k - 1][x1][x2]> f[k][x1][x2]) f[k][x1][x2] = f[k - 1][x1][x2];
				if(y1 > 1 && x2 > 1 && f[k - 1][x1][x2 - 1] > f[k][x1][x2]) f[k][x1][x2] = f[k - 1][x1][x2 - 1];
				if(x1 > 1 && y2 > 1 && f[k - 1][x1 - 1][x2] > f[k][x1][x2]) f[k][x1][x2] = f[k - 1][x1 - 1][x2];
				if(x1 > 1 && x2 > 1 && f[k - 1][x1 - 1][x2 - 1] > f[k][x1][x2]) f[k][x1][x2] = f[k - 1][x1 - 1][x2 - 1];
				f[k][x1][x2] += num[x1][y1] + num[x2][y2];
			}
	if(f[n + m - 3][n][n - 1] > f[n + m - 3][n - 1][n]) printf("%d\n", f[n + m - 3][n][n - 1]);
	else printf("%d\n",f[n + m - 3][n - 1][n]);
}
