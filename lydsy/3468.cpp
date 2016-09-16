#include <cstdio>
#include <cstring>
const int maxn = 301, maxk = 201, mod = 12345, maxd = 4, dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int n, m, k, a[maxn][maxn], f[2][maxn][maxn], pre = 1, cur, g[maxk], s[maxk][maxk], fact[maxk], ans[maxk];
bool vis[maxn][maxn];
void dfs(int x, int y, int k)
{
	if(vis[x][y])
		return;
	vis[x][y] = 1;
	for(int d = 0; d < maxd; ++d)
	{
		int xx = x + dx[d], yy = y + dy[d];
		if(xx && xx <= n && yy && yy <= m && a[x][y] > a[xx][yy])
		{
			dfs(xx, yy, k);
			if((f[cur][x][y] += f[pre][xx][yy]) >= mod)
				f[cur][x][y] -= mod;
			if((f[cur][x][y] += f[cur][xx][yy]) >= mod)
				f[cur][x][y] -= mod;
			if(k <= 1 && ++f[cur][x][y] >= mod)
				f[cur][x][y] -= mod;
		}
	}
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%d", a[i] + j);
	for(int o = 0; o <= k; ++o)
	{
		pre ^= 1;
		cur ^= 1;
		memset(f[cur], 0, sizeof f[0]);
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				dfs(i, j, o);
				if((g[o] += f[cur][i][j]) >= mod)
					g[o] -= mod;
			}
	}
	fact[0] = 1;
	ans[0] = g[0];
	for(int i = 1; i <= k; ++i)
	{
		fact[i] = fact[i - 1] * i % mod;
		for(int j = 1; j < i; ++j)
			s[i][j] = (s[i - 1][j - 1] + s[i - 1][j] * j) % mod;
		s[i][i] = 1;
		for(int j = 1; j <= i; ++j)
			ans[i] = (ans[i] + s[i][j] * fact[j] * (long long)g[j]) % mod;
	}
	for(int i = 0; i <= k; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
