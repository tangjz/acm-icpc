#include <cstdio>
#include <cstring>
const int maxn = 301, maxe = 100001;
int n, lim, m, a[maxn], b[maxn], g[maxn], tot, len, path[maxn], cnt, ans[maxn * maxn * 2][3];
bool vis[maxn];
struct Edge
{
	int nxt, v;
} e[maxe];
int min(int x, int y)
{
	return x < y ? x : y;
}
void dfs(int u)
{
	vis[u] = 1;
	path[len++] = u;
	if(a[u] < b[u])
	{
		int &sta = path[0], &end = path[len - 1];
		int cost = min(a[sta] - b[sta], b[end] - a[end]);
		if(cost)
		{
			for(int i = 0; i < len - 1; ++i)
			{
				int flow = min(cost, lim - a[path[i + 1]]);
				if(flow)
				{
					ans[cnt][0] = path[i];
					ans[cnt][1] = path[i + 1];
					ans[cnt++][2] = flow;
				}
			}
			for(int i = len - 2; i >= 0; --i)
			{
				int flow = cost - min(cost, lim - a[path[i + 1]]);
				if(flow)
				{
					ans[cnt][0] = path[i];
					ans[cnt][1] = path[i + 1];
					ans[cnt++][2] = flow;
				}
			}
			a[sta] -= cost;
			a[end] += cost;
		}
	}
	for(int it = g[u]; it; it = e[it].nxt)
		if(!vis[e[it].v])
			dfs(e[it].v);
	--len;
}
int main()
{
	scanf("%d%d%d", &n, &lim, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", b + i);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){g[u], v};
		g[u] = tot;
		e[++tot] = (Edge){g[v], u};
		g[v] = tot;
	}
	for(int i = 1; i <= n; ++i)
		if(a[i] > b[i])
		{
			memset(vis, 0, sizeof vis);
			dfs(i);
		}
	for(int i = 1; i <= n; ++i)
		if(a[i] != b[i])
		{
			puts("NO");
			return 0;
		}
	printf("%d\n", cnt);
	for(int i = 0; i < cnt; ++i)
		printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
	return 0;
}
