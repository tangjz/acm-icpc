#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 50001;
int n, m, tim[maxn], dsu[2][maxn], fa[maxn], rt[maxn], low[2][maxn];
std::vector<int> e[maxn], g[maxn];
int dsu_find(int dsu[], int x)
{
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu, dsu[x]));
}
void dsu_merge(int dsu[], int u, int v)
{
	u = dsu_find(dsu, u);
	v = dsu_find(dsu, v);
	if(u == v)
		return;
	if(dsu[u] > dsu[v])
		std::swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[u];
	dsu[v] = u;
}
inline int& bin_root(int u)
{
	return rt[dsu_find(dsu[0], u)];
}
void low_upd(int u, int v)
{
	if(tim[v] < tim[low[0][u]])
	{
		low[1][u] = low[0][u];
		low[0][u] = v;
	}
	else if(tim[v] < tim[low[1][u]])
		low[1][u] = v;
}
void tarjan(int u)
{
	tim[u] = ++m;
	low[0][u] = low[1][u] = u;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it;
		if(v == fa[u])
			continue;
		if(!tim[v])
		{
			fa[v] = u;
			tarjan(v);
			int best = u;
			for(std::vector<int>::iterator jt = g[u].begin(); jt != g[u].end(); ++jt)
			{ // iterate all return edge from the subtree of v
				for(int w = bin_root(*jt); w != bin_root(u); w = bin_root(fa[w]))
				{ // merge all possible biconnect blocks
					if(tim[low[1][w]] < tim[best])
						best = low[1][w];
					dsu_merge(dsu[0], u, w); // biconnect
				}
			}
			std::vector<int>().swap(g[u]);
			low_upd(u, low[0][v]); // update for biconnect
			low_upd(u, best); // update for triconnect, that means there exists at least one w make u-w-low[0][w]-best, u-w-best, best-u possible
		}
		else if(tim[v] < tim[u]) // a return edge is occurred
		{
			low_upd(u, v); // update for biconnect
			g[v].push_back(u);
		}
	}
	bin_root(u) = u; // biconnect root
	dsu_merge(dsu[1], u, low[1][u]); // triconnect, if not get from w, that means u-low[0][u], u-low[1][u], low[1][u]-u are possible
}
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	m = 0;
	memset(dsu[0] + 1, -1, n * sizeof(int));
	memset(dsu[1] + 1, -1, n * sizeof(int));
	for(int i = 1; i <= n; ++i)
		if(!tim[i])
			tarjan(i);
	scanf("%d", &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		puts(dsu_find(dsu[1], u) == dsu_find(dsu[1], v) ? "Yes" : "No");
	}
	return 0;
}