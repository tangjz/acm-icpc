#include <queue>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<LL, int> Edge;
const int maxn = 200001, maxd = 19;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, S, deg[maxn], que[maxn], L, R, dep[maxn], fa[maxd][maxn], sz[maxn], ctr[maxn];
LL dis[maxn];
vector<Edge> e[maxn];
priority_queue<Edge, vector<Edge>, greater<Edge> > Q;
bool vis[maxn];
int lca(int u, int v)
{
	if(dep[u] > dep[v])
		swap(u, v);
	for(int i = dep[v] - dep[u], j = 0; i; i >>= 1, ++j)
		if(i & 1)
			v = fa[j][v];
	if(u == v)
		return u;
	for(int i = maxd - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v])
		{
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
int main()
{
	scanf("%d%d%d", &n, &m, &S);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(make_pair((LL)w, v));
		e[v].push_back(make_pair((LL)w, u));
	}
	memset(dis + 1, 0x3f, n * sizeof(LL));
	dis[S] = 0;
	Q.push(make_pair(dis[S], S));
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(auto &it : e[u])
		{
			int v = it.second;
			LL dist = dis[u] + it.first;
			if(dis[v] > dist)
			{
				dis[v] = dist;
				Q.push(make_pair(dis[v], v));
			}
		}
	}
	for(int u = 1; u <= n; ++u)
		if(dis[u] != INF)
		{
			vector<Edge> tmp;
			for(auto &it : e[u])
				if(dis[it.second] == dis[u] + it.first)
				{
					tmp.push_back(it);
					++deg[it.second];
				}
			e[u].swap(tmp);
		}
	memcpy(ctr + 1, deg + 1, n * sizeof(int));
	L = R = 0;
	que[R++] = S;
	while(L < R)
	{
		int u = que[L++];
		for(auto &it : e[u])
		{
			int v = it.second;
			if(!(--ctr[v]))
				que[R++] = v;
		}
	}
	for(int i = 0; i < R; ++i)
	{
		int u = que[i];
		dep[u] = dep[fa[0][u]] + 1;
		for(int d = 1; d < maxd; ++d)
			fa[d][u] = fa[d - 1][fa[d - 1][u]];
		for(auto &it : e[u])
		{
			int v = it.second;
			if(!fa[0][v])
				fa[0][v] = u;
			else
				fa[0][v] = lca(u, fa[0][v]);
		}
	}
	int ans = 0;
	for(int i = R - 1; i > 0; --i)
	{
		int u = que[i];
		++sz[u];
		sz[fa[0][u]] += sz[u];
		if(ans < sz[u])
			ans = sz[u];
	}
	printf("%d\n", ans);
}
