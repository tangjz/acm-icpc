#include <cstdio>
#include <cstring>
const int maxn = 2002, mod = 1000000007;
int n, k, tot, pre[maxn], f[maxn][maxn], g[maxn][maxn], s[maxn];
struct Edge
{
	int nxt, v;
} e[maxn << 1];
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
void dfs(int u, int fa)
{
	f[u][s[u] = 1] = 1;
	for(int it = pre[u]; it; it = e[it].nxt)
	{
		if(e[it].v == fa)
			continue;
		dfs(e[it].v, u);
		s[u] += s[e[it].v];
		for(int i = s[u]; i > 0; --i)
		{
			f[u][i] = (long long)f[u][i] * g[e[it].v][k] % mod;
			for(int j = 1; j < i; ++j)
				inc(f[u][i], (long long)f[u][j] * f[e[it].v][i - j] % mod);
		}
	}
	memcpy(g[u], f[u], (s[u] + 1) * sizeof(int));
	for(int i = s[u]; i > 0; --i)
		inc(g[u][i], g[u][i + 1]);
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1, u, v; i < n; ++i)
	{
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){pre[u], v};
		pre[u] = tot;
		e[++tot] = (Edge){pre[v], u};
		pre[v] = tot;
	}
	dfs(1, -1);
	printf("%d\n", g[1][k]);
	return 0;
}
