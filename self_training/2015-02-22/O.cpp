#include <cstdio>
#include <cstring>
const int maxn = 201, maxm = 10001;
int t, n, m, a[maxm], b[maxm], c[maxm], tot, pre[maxn << 1][2], cnt, seq[maxn << 1], sum, scc[maxn << 1];
bool vis[maxn << 1];
struct Edge
{
	int nxt, v;
} e[maxm << 3];
void addedge(int u, int v)
{
	e[++tot] = (Edge){pre[u][0], v};
	pre[u][0] = tot;
	e[++tot] = (Edge){pre[v][1], u};
	pre[v][1] = tot;
}
void dfs1(int u)
{
	vis[u] = 1;
	for(int it = pre[u][0]; it; it = e[it].nxt)
		if(!vis[e[it].v])
			dfs1(e[it].v);
	seq[cnt++] = u;
}
void dfs2(int u)
{
	vis[u] = 1;
	scc[u] = sum;
	for(int it = pre[u][1]; it; it = e[it].nxt)
		if(!vis[e[it].v])
			dfs2(e[it].v);
}
bool check(int m)
{
	tot = 0;
	memset(pre, 0, sizeof pre);
	for(int i = 0; i < m; ++i)
		switch(c[i])
		{
			case 0: addedge(n + a[i], b[i]); addedge(n + b[i], a[i]); break; 
			case 1: addedge(a[i], b[i]); addedge(b[i], a[i]); addedge(n + a[i], n + b[i]); addedge(n + b[i], n + a[i]); break;
			case 2: addedge(a[i], n + b[i]); addedge(b[i], n + a[i]); break;
		}
	cnt = 0;
	memset(vis, 0, sizeof vis);
	for(int i = 0; i < n << 1; ++i)
		if(!vis[i])
			dfs1(i);
	sum = 0;
	memset(vis, 0, sizeof vis);
	for(int i = (n << 1) - 1; i >= 0; --i)
		if(!vis[seq[i]])
		{
			++sum;
			dfs2(seq[i]);
		}
	for(int i = 0; i < n; ++i)
		if(scc[i] == scc[n + i])
			return 0;
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++i)
			scanf("%d%d%d", a + i, b + i, c + i);
		int L = 0, R = m, M;
		while(L < R)
		{
			M = L + R + 1 >> 1;
			if(check(M))
				L = M;
			else
				R = M - 1; 
		}
		printf("%d\n", L);
	}
	return 0;
}
