#include <cstdio>
#include <cstring>
const int maxn = 100010, maxd = 18;
int n, q, nxt[maxn], now, tot, cir[maxn], cir_cnt[maxn], cir_no[maxn], fa[maxn][maxd], gen[maxn];
int dfsno[maxn], vis[maxn], dep[maxn];
void pfs(int u)
{
	dfsno[u] = now;
	if(!dfsno[nxt[u]])
	{
		pfs(nxt[u]);
	}
	else if(dfsno[nxt[u]] == now)
	{
		cir[u] = ++tot;
		cir_cnt[tot] = 1;
		cir_no[u] = 1;
		//printf("%d : %d\n", tot, u);
		for(int i = nxt[u], last = u; i != u; last = i, i = nxt[i])
		{
			//printf("%d : %d\n", tot, i);
			cir[i] = cir[last];
			cir_no[i] = cir_no[last] + 1;
			++cir_cnt[tot];
		}
	}
}
void dfs(int u)
{
	vis[u] = 1;
	if(!cir[u])
	{
		fa[u][0] = nxt[u];
		if(!vis[nxt[u]])
			dfs(nxt[u]);
		gen[u] = gen[nxt[u]];
		dep[u] = dep[nxt[u]] + 1;
	}
	else
	{
		fa[u][0] = 0;
		gen[u] = u;
		dep[u] = 0;
	}
}
int lca(int u, int v)
{
	if(dep[u] > dep[v])
	{
		int t = u;
		u = v;
		v = t;
	}
	for(int i = 0, j = dep[v] - dep[u]; i < maxd && j > 0; ++i, j >>= 1)
		if(j & 1)
			v = fa[v][i];
	if(u == v)
		return u;
	for(int i = maxd - 1; i >= 0; --i)
		if(fa[u][i] != fa[v][i])
		{
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}
int dist(int u, int v)
{
	return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		tot = 0;
		memset(cir, 0, sizeof cir);
		memset(dep, 0, sizeof dep);
		memset(dfsno, 0, sizeof dfsno);
		memset(cir_no, 0, sizeof cir_no);
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= n; ++i)
			scanf("%d",nxt + i);
		for(int i = 1; i <= n; ++i)
			if(!dfsno[i])
			{
				now = i;
				pfs(i);
			}
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
				dfs(i);
		for(int d = 1; d < maxd; ++d)
			for(int i = 1; i <= n; ++i)
				fa[i][d] = fa[fa[i][d - 1]][d - 1];
		scanf("%d", &q);
		for(int i = 0; i < q; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			//printf("%d %d : %d %d : %d %d\n", u, v, gen[u], gen[v], cir[gen[u]], cir[gen[v]]);
			if(cir[gen[u]] != cir[gen[v]])
				puts("-1");
			else if(gen[u] == gen[v])
				printf("%d\n", dist(u, v));
			else
			{
				int tmp1 = dep[u] + dep[v], tmp2 = cir_no[gen[u]] - cir_no[gen[v]];
				//printf("%d->%d : %d\n", u, gen[u], dep[u]);
				//printf("%d->%d : %d\n", v, gen[v], dep[v]);
				if(tmp2 < 0)
					tmp2 = -tmp2;
				//printf("%d %d : %d %d\n", cir_no[gen[u]], cir_cnt[cir[gen[u]]], tmp2, cir_cnt[cir[gen[u]]] - tmp2);
				if(tmp2 > cir_cnt[cir[gen[u]]] - tmp2)
					tmp2 = cir_cnt[cir[gen[u]]] - tmp2;
				printf("%d\n", tmp1 + tmp2);
			}
		}
	}
	return 0;
}
