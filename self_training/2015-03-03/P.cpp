#include <cmath>
#include <cstdio>
#include <cstring>
const int maxn = 10001;
int t, n, tot, deg[maxn], pre[maxn], nxt[maxn << 1], to[maxn << 1];
double k[maxn], e[maxn], f[maxn], g[maxn], h[maxn];
bool vis[maxn];
bool check(int u)
{
	vis[u] = 1;
	if(e[u])
		return 1;
	else if(k[u] == 100)
		return 0;
	for(int it = pre[u]; it; it = nxt[it])
		if(!vis[to[it]] && check(to[it]))
			return 1;
	return 0;
}
void dfs(int u)
{
	vis[u] = 1;
	double fact = 0;
	for(int it = pre[u]; it; it = nxt[it])
	{
		int &v = to[it];
		if(vis[v])
			continue;
		dfs(v);
		f[u] += f[v];
		h[u] += h[v];
		fact += g[v];
	}
	g[u] = (1 - k[u] - e[u]) / deg[u];
	fact *= g[u];
	f[u] = (k[u] + g[u] * f[u]) / (1 - fact);
	h[u] = (1 - k[u] - e[u] + g[u] * h[u]) / (1 - fact);
	g[u] /= 1 - fact;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		tot = 0;
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		memset(h, 0, sizeof h);
		memset(vis, 0, sizeof vis);
		memset(deg, 0, sizeof deg);
		memset(pre, 0, sizeof pre);
		scanf("%d", &n);
		for(int i = 1, u, v; i < n; ++i)
		{
			scanf("%d%d", &u, &v);
			++deg[u];
			to[++tot] = v;
			nxt[tot] = pre[u];
			pre[u] = tot;
			++deg[v];
			to[++tot] = u;
			nxt[tot] = pre[v];
			pre[v] = tot;
		}
		for(int i = 1; i <= n; ++i)
			scanf("%lf%lf", k + i, e + i);
		if(!check(1))
		{
			printf("Case %d: impossible\n", Case);
			continue;
		}
		for(int i = 1; i <= n; ++i)
		{
			k[i] /= 100;
			e[i] /= 100;
		}
		memset(vis, 0, sizeof vis);
		dfs(1);
		printf("Case %d: %.5f\n", Case, h[1] / (1 - f[1]));
	}
	return 0;
}
