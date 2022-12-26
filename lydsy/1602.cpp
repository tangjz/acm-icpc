/*
 * 随机挑一个点为根
 * 设dis[i]为i到根的距离
 * 询问 u到v的距离 = dis[u] + dis[v] - dis[lca[u][v]] * 2
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
vector<edge> g[1001];
int n, q, level[1001] = {}, dis[1001] = {};
void dfs(int u, int sum, int dep)
{
	int v1, v2;
	dis[u] = sum;
	level[u] = dep;
	v1 = g[u][0].first;
	if(!level[v1]) dfs(v1, sum + g[u][0].second, dep + 1);
	if(g[u].size() == 1) return;
	for(int i = 1; i < (int)g[u].size(); ++i)
	{
		v2 = g[u][i].first;
		if(!level[v2]) dfs(v2, sum + g[u][i].second, dep + 1);
		else swap(g[u][0], g[u][i]);
	}
}
int lca(int u, int v)
{
	while(level[u] > level[v]) u = g[u][0].first;
	while(level[u] < level[v]) v = g[v][0].first;
	while(u != v) { u = g[u][0].first; v = g[v][0].first; }
	return u;
}
int main()
{
	int i, j, k, w;
	scanf("%d%d", &n, &q);
	for(i = 1; i < n; ++i)
	{
		scanf("%d%d%d", &j, &k, &w);
		g[j].push_back(make_pair(k, w));
		g[k].push_back(make_pair(j, w));
	}
	dfs(1, 0, 1);
	for(i = 1; i <= q; ++i)
	{
		scanf("%d%d", &j, &k);
		printf("%d\n", dis[j] + dis[k] - dis[lca(j, k)] * 2);
	}
	return 0;
}
