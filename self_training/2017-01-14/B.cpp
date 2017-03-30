#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100001, INF = 0x3f3f3f3f;
int n, f[maxn], g[maxn], ff[maxn], gg[maxn];
bool vis[maxn];
std::vector<std::pair<int, int> > e[maxn];
void dfs1(int u)
{
	vis[u] = 1;
	f[u] = 0, g[u] = 1;
	ff[u] = -INF, gg[u] = 0;
	for(std::vector<std::pair<int, int> >::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = it -> first, w = it -> second;
		if(vis[v])
			continue;
		dfs1(v);
		if(f[u] <= f[v] + w)
		{
			if(f[u] < f[v] + w)
			{
				ff[u] = f[u];
				gg[u] = g[u];
				f[u] = f[v] + w;
				g[u] = g[v];
			}
			else
				g[u] += g[v];
		}
		else if(ff[u] <= f[v] + w)
		{
			if(ff[u] < f[v] + w)
			{
				ff[u] = f[v] + w;
				gg[u] = g[v];
			}
			else
				gg[u] += g[v];
		}
	}
}
void dfs2(int u)
{
	vis[u] = 1;
	for(std::vector<std::pair<int, int> >::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = it -> first, w = it -> second;
		if(vis[v])
			continue;
		int dis, way;
		if(f[u] == f[v] + w && g[u] == g[v]) // second
		{
			dis = ff[u];
			way = gg[u];
		}
		else
		{
			dis = f[u];
			way = g[u] - (f[u] == f[v] + w ? g[v] : 0);
		}
		if(f[v] <= dis + w)
		{
			if(f[v] < dis + w)
			{
				ff[v] = f[v];
				gg[v] = g[v];
				f[v] = dis + w;
				g[v] = way;
			}
			else
				g[v] += way;
		}
		else if(ff[v] <= dis + w)
		{
			if(ff[v] < dis + w)
			{
				ff[v] = dis + w;
				gg[v] = way;
			}
			else
				gg[v] += way;
		}
		dfs2(v);
	}
}
int main()
{
	for(int Case = 1; scanf("%d", &n) == 1; ++Case)
	{
		for(int i = 1; i <= n; ++i)
			std::vector<std::pair<int, int> >().swap(e[i]);
		for(int i = 1; i < n; ++i)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			e[u].push_back(std::make_pair(v, w));
			e[v].push_back(std::make_pair(u, w));
		}
		memset(vis, 0, sizeof vis);
		dfs1(1);
		memset(vis, 0, sizeof vis);
		dfs2(1);
		printf("Case #%d:", Case);
		for(int i = 1; i <= n; ++i)
			printf(" %d", g[i]);
		putchar('\n');
	}
	return 0;
}
