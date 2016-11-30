#include <cstdio>
#include <cstring>
const int maxn = 301, maxk = 301;
const long long INF = (0x3f3f3f3fll << 32) + 0x3f3f3f3f;
int n, m, k;
long long g[maxn][maxn], f[maxn][maxk], ans;
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	memset(f, 0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	while(m--)
	{
		int l, r, c;
		scanf("%d%d%d", &l, &r, &c);
		if(g[l - 1][r] > c)
			g[l - 1][r] = c;
	}
	for(int i = 0; i <= n; ++i)
		for(int j = n; j > i; --j)
		{
			if(g[i + 1][j] > g[i][j])
				g[i + 1][j] = g[i][j];
			if(g[i][j - 1] > g[i][j])
				g[i][j - 1] = g[i][j];
		}
	f[0][0] = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= i; ++j)
		{
			f[i][j] = f[i - 1][j];
			for(int k = i - j; k < i; ++k)
				if(f[i][j] > f[k][j - i + k] + g[k][i])
					f[i][j] = f[k][j - i + k] + g[k][i];
		}
	ans = f[n][k];
	for(int i = k + 1; i <= n; ++i)
		if(ans > f[n][i])
			ans = f[n][i];
	if(ans != INF)
		printf("%I64d\n", ans);
	else
		puts("-1");
	return 0;
}
