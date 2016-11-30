#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 1001;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, a[maxn][maxn];
LL s[maxn][maxn], f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], ans;

int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= i; ++j)
				scanf("%d", a[i - j + 1] + j);
		for(int i = 1, lim = n; i <= n; ++i, --lim)
		{
			for(int j = 1; j <= lim; ++j)
			{
				s[i][j] = a[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
				f[i][j] = h[i - 1][j] + s[i][j];
				ans = std::max(ans, f[i][j]);
			}
			g[i][lim + 1] = -INF;
			for(int j = lim; j >= 1; --j)
				g[i][j] = std::max(g[i][j + 1], f[i][j]);
			for(int j = 1; j <= lim; ++j)
				h[i][j] = std::max(h[i - 1][j], g[i][j + 1] - s[i][j]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
