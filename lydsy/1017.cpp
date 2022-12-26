#include <cstdio>
const int maxn = 52, maxm = 2001, INF = 0x3f3f3f3f;
int n, m, root, c[maxn], s[maxn], w[maxn], f[maxn][maxm], g[maxn][maxm], h[maxn][maxm], ans;
int tot, pre[maxn];
struct Edge
{
	int nxt, v, cnt;
} e[maxn];
bool vis[maxn];
void dfs1(int u)
{
	if(!pre[u])
		return;
	s[u] = INF;
	for(int it = pre[u]; it; it = e[it].nxt)
	{
		int &v = e[it].v, &cnt = e[it].cnt;
		dfs1(v);
		c[u] += c[v] * cnt;
		if(s[u] > s[v] / cnt)
			s[u] = s[v] / cnt;
	}
	if(s[u] > m / c[u])
		s[u] = m / c[u];
}
bool merge(int f[], int g[])
{
	bool flag = 0;
	for(int i = m - 1; i >= 0; --i)
	{
		if(i && !f[i])
			continue;
		for(int j = 1; i + j <= m; ++j)
			if(g[j] && f[i + j] < f[i] + g[j])
			{
				f[i + j] = f[i] + g[j];
				flag = 1;
			}
	}
	int maxw = 0;
	for(int i = 0; i <= m; ++i)
		if(maxw < f[i])
			maxw = f[i];
		else
			f[i] = 0;//最优解, 配合上面continue剪枝
	return flag;
}
void dfs2(int u, int lim)
{
	for(int it = pre[u]; it; it = e[it].nxt)
	{
		int &v = e[it].v, &cnt = e[it].cnt;
		dfs2(v, s[u] * cnt);
		merge(h[u], f[v]);
		for(int i = 0; i < cnt; ++i)
			if(!merge(g[u], g[v]))
				break;
	}
	bool flag = 1;
	for(int i = s[u] - lim; i >= 0; --i)
	{
		int uc = c[u] * i, uw = w[u] * i;
		for(int j = uc; j <= m; ++j)
			if(f[u][j] < h[u][j - uc] + uw)
				f[u][j] = h[u][j - uc] + uw;
		if(flag)
			flag = merge(h[u], g[u]);
	}
	if(c[u] <= m && g[u][c[u]] < w[u])
		g[u][c[u]] = w[u];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		char type;
		scanf("%d %c", w + i, &type);
		if(type == 'A')
		{
			int c, id, size;
			scanf("%d", &c);
			while(c--)
			{
				scanf("%d%d", &id, &size);
				e[++tot] = (Edge){pre[i], id, size};
				pre[i] = tot;
				vis[id] = 1;
			}
		}
		else
			scanf("%d%d", c + i, s + i);
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
		{
			root = i;
			break;
		}
	dfs1(root);
	dfs2(root, 0);
	for(int i = 0; i <= m; ++i)
		if(ans < f[root][i])
			ans = f[root][i];
	printf("%d\n", ans);
	return 0;
}
