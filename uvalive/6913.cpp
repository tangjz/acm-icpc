#include <cstdio>
#include <cstring>
const int maxn = 2010;
int t, n, m, k, tot, a[maxn], f[maxn][maxn], g[maxn][maxn];
char str[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		tot = 0;
		scanf("%d%d%d%s", &n, &m, &k, str);
		for(int i = 0, j = 0; i < 2 * n; i = j)
		{
			while(j < 2 * n && str[i] == str[j])
				++j;
			a[tot++] = j - i;
		}
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		f[tot - 1][0] = 0;
		for(int i = 1; i <= a[tot - 1] * k && i <= m; ++i)
			f[tot - 1][i] = 1;
		for(int i = a[tot - 1] * k + 1; i <= m; ++i)
			f[tot - 1][i] = 0;
		for(int i = 1; i <= m; ++i)
			g[tot - 1][i] = g[tot - 1][i - 1] + f[tot - 1][i];
		for(int i = tot - 2; i >= 0; --i)
		{
			f[i][0] = 0;
			for(int j = 1; j <= a[i] * k && j <= m; ++j)
				f[i][j] = 1;
			for(int j = a[i] * k + 1; j <= m; ++j)
				if(g[i + 1][j - a[i]] - g[i + 1][j - a[i] * k - 1] == a[i] * (k - 1) + 1)
					f[i][j] = 0;
				else
					f[i][j] = 1;
			for(int j = 1; j <= m; ++j)
				g[i][j] = g[i][j - 1] + f[i][j];
		}
		/*for(int i = 0; i < tot; ++i)
		{
			for(int j = 0; j <= m; ++j)
				printf("%d ", f[i][j]);
			putchar('\n');
		}*/
		printf("Case #%d: %c\n", Case, 'A' + ((str[0] - 'A') ^ (f[0][m] ^ 1)));
	}
	return 0;
}
