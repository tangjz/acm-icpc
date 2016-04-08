#include <cstdio>
const int maxn = 200001, maxm = 200001;
int n, m, d, tot, pre[maxn], deg[maxn], que[maxn], L, R, fa[maxn], sz[maxn];
struct Edge
{
	int nxt, v;
} e[maxm << 1];
bool vis[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d%d", &n, &m, &d);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){pre[u], v};
		pre[u] = tot;
		++deg[u];
		e[++tot] = (Edge){pre[v], u};
		pre[v] = tot;
		++deg[v];
	}
	for(int i = 1; i <= n; ++i)
		if(deg[i] < d)
		{
			que[R++] = i;
			vis[i] = 1;
		}
	while(L < R)
	{
		int &u = que[L++];
		for(int it = pre[u]; it; it = e[it].nxt)
		{
			int &v = e[it].v;
			if(vis[v])
				continue;
			if(--deg[v] < d)
			{
				que[R++] = v;
				vis[v] = 1;
			}
		}
	}
	if(R == n)
		puts("NIE");
	else
	{
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
			{
				fa[i] = i;
				sz[i] = 1;
			}
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
				for(int it = pre[i]; it; it = e[it].nxt)
					if(!vis[e[it].v] && find(i) != find(e[it].v))
					{
						sz[find(i)] += sz[find(e[it].v)];
						fa[find(e[it].v)] = find(i);
					}
		int pos = -1;
		for(int i = 1; i <= n; ++i)
			if(!vis[i] && i == find(i) && (pos == -1 || sz[pos] < sz[i]))
				pos = i;
		printf("%d\n", sz[pos]);
		for(int i = 1; i <= n; ++i)
			if(!vis[i] && find(i) == pos)
				printf("%d ", i);
		putchar('\n');
	}
	return 0;
}
