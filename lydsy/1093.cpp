#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 1000001;
int n, m, mod, tot, pre[maxn], suf[maxn], que[maxn], scc_tot, scc[maxn], cnt[maxn];
pair<int, int> e[maxm], g[maxm << 1], f[maxn], ans;
bool vis[maxn];
void dfs1(int u)
{
	vis[u] = 1;
	for(int it = pre[u]; it; it = g[it].first)
		if(!vis[g[it].second])
			dfs1(g[it].second);
	que[tot++] = u;
}
void dfs2(int u)
{
	vis[u] = 1;
	scc[u] = scc_tot;
	++cnt[scc_tot];
	for(int it = suf[u]; it; it = g[it].first)
		if(!vis[g[it].second])
			dfs2(g[it].second);
}
void dfs3(int u)
{
	vis[u] = 1;
	f[u] = {0, 1};
	for(int it = suf[u]; it; it = g[it].first)
	{
		int &v = g[it].second;
		if(!vis[v])
			dfs3(v);
		if(f[u].first < f[v].first)
			f[u] = f[v];
		else if(f[u].first == f[v].first)
		{
			f[u].second += f[v].second;
			if(f[u].second >= mod)
				f[u].second -= mod;
		}
	}
	f[u].first += cnt[u];
}
int main()
{
	scanf("%d%d%d", &n, &m, &mod);
	for(int i = 0; i < m; ++i)
	{
		int &u = e[i].first, &v = e[i].second;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		g[++tot] = {pre[u], v};
		pre[u] = tot;
		g[++tot] = {suf[v], u};
		suf[v] = tot;
	}
	tot = 0;
	for(int i = 0; i < n; ++i)
		if(!vis[i])
			dfs1(i);
	memset(vis, 0, n * sizeof(bool));
	for(int i = n - 1; i >= 0; --i)
		if(!vis[que[i]])
		{
			dfs2(que[i]);
			++scc_tot;
		}
	tot = 0;
	for(int i = 0; i < m; ++i)
	{
		int &u = e[i].first, &v = e[i].second;
		if(scc[u] != scc[v])
			e[tot++] = {scc[u], scc[v]};
	}
	m = tot;
	sort(e, e + m);
	m = unique(e, e + m) - e;
	tot = 0;
	memset(suf, 0, scc_tot * sizeof(int));
	for(int i = 0; i < m; ++i)
	{
		int &u = e[i].first, &v = e[i].second;
		g[++tot] = {suf[v], u};
		suf[v] = tot;
	}
	ans = {0, 1};
	memset(vis, 0, scc_tot * sizeof(bool));
	for(int i = 0; i < scc_tot; ++i)
		if(!vis[i])
		{
			dfs3(i);
			if(ans.first < f[i].first)
				ans = f[i];
			else if(ans.first == f[i].first)
			{
				ans.second += f[i].second;
				if(ans.second >= mod)
					ans.second -= mod;
			}
		}
	printf("%d\n%d\n", ans.first, ans.second);
	return 0;
}
