#include <cstdio>
#include <cstring>
const int maxn = 10001, maxm = 100001;
int n, m, s, t, tot, lnk[maxn], pre[maxn];
bool vis[maxn], used[maxm << 1];
struct Edge
{
	int nxt, v;
} e[maxm << 1];
int tarjan(int u, int fa)
{
	int lowu = pre[u] = ++tot;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		if(fa == (it ^ 1))
			continue;
		int &v = e[it].v;
		if(!pre[v])
		{
			int lowv = tarjan(v, it);
			if(lowu > lowv)
				lowu = lowv;
			if(pre[u] < lowv)
				used[it] = used[it ^ 1] = 1;
		}
		else if(lowu > pre[v])
			lowu = pre[v];
	}
	return lowu;
}
void dfs(int u)
{
	vis[u] = 1;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(!used[it] && !vis[e[it].v])
			dfs(e[it].v);
}
int main()
{
	for(int Case = 1; scanf("%d%d", &n, &m) == 2 && n + m; ++Case)
	{
		tot = 0;
		memset(pre, 0, n * sizeof(int));
		memset(lnk, -1, n * sizeof(int));
		memset(used, 0, (m << 1) * sizeof(bool));
		memset(vis, 0, n * sizeof(bool));
		while(m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			--u;
			--v;
			e[tot] = (Edge){lnk[u], v};
			lnk[u] = tot++;
			e[tot] = (Edge){lnk[v], u};
			lnk[v] = tot++;
		}
		scanf("%d%d", &s, &t);
		--s;
		--t;
		tot = 0;
		tarjan(s, -1);
		dfs(s);
		printf("Case %d: %s\n", Case, vis[t] ? "YES" : "NO");
	}
	return 0;
}
