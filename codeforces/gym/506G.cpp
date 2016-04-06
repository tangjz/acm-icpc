#include <cstdio>
#include <cstring>
const int maxn = 101;
int t, n, m;
char g[maxn][maxn];
double f[maxn][maxn], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(f, 0, sizeof f);
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%s", g[i]);
		for(int i = n - 1; i >= 0; --i)
			for(int j = 0; j < m; ++j)
				if(g[i][j] >= '0' && g[i][j] <= '9')
					f[i][j] = g[i][j] - '0';
				else if(g[i][j] == '*')
					f[i][j] = ((j > 0 ? f[i + 1][j - 1] : 0) + (j < m - 1 ? f[i + 1][j + 1] : 0)) / 2;
				else
					f[i][j] = f[i + 1][j];
		ans = f[0][0];
		for(int i = 1; i < m; ++i)
			if(ans < f[0][i])
				ans = f[0][i];
		printf("%.8f\n", ans);
	}
	return 0;
}
