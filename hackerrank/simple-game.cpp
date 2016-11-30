#include <stdio.h>
#include <cstring>
const int maxn = 601, maxm = 11, maxs = 1 << 10, mod = 1000000007;
int n, m, p, f[maxm][maxn][maxs], g[maxn];
void upd(int &x, int y)
{
	if((x += y) >= mod)
		x -= mod;
}
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	if(p == 2)
		for(int i = 2; i <= n; ++i)
			g[i] = ~i & 1;
	else if(p > 3)
		for(int i = 2; i <= n; ++i)
			g[i] = i - 1;
	else
	{
		static int vis[maxs] = {};
		for(int i = 2; i <= n; ++i)
		{
			memset(vis, 0, sizeof vis);
			for(int j = 1; j <= i - j; ++j)
			{
				vis[g[j] ^ g[i - j]] = 1;
				for(int k = j; k <= i - j - k; ++k)
					vis[g[j] ^ g[k] ^ g[i - j - k]] = 1;
			}
			for(g[i] = 0; vis[g[i]]; ++g[i]);
		}
	}
	f[0][0][0] = 1;
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j)
			for(int k = 0; k < maxs; ++k)
				if(f[i][j][k])
					for(int d = 1; j + d <= n; ++d)
						upd(f[i + 1][j + d][k ^ g[d]], f[i][j][k]);
	int ans = 0;
	for(int k = 1; k < maxs; ++k)
		upd(ans, f[m][n][k]);
	printf("%d\n", ans);
	return 0;
}
