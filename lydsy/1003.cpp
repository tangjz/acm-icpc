/*
 * 令f[i]表示运输进行到第i天所需要的最小成本，有f[i] = min(f[j] + cost(j+1, i) * (i - j) + k)
 * cost(i,j)表示第i天到第j天都能通行的最短路径 做dijkstra
 */
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
priority_queue<edge, vector<edge>, greater<edge> > Q;
struct Line { int v, w, next; } line[801] = {};
int n, m, k, e, d, head[21] = {}, dist[21] = {}, f[101] = {};
bool flag[21][101] = {}, vis[21];
int shortest(const int s, const int t)
{
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= m; ++i)
		for(int j = s; j <= t; ++j) if(flag[i][j]) { vis[i] = true; break; }
	dist[1] = 0;
	Q.push(make_pair(0, 1));
	while(!Q.empty())
	{
		int u = (Q.top()).second; Q.pop();
		if(vis[u]) continue;
		for(int v = head[u]; v; v = line[v].next)
		{
			if(vis[line[v].v]) continue;
			if(dist[u] + line[v].w < dist[line[v].v])
			{
				dist[line[v].v] = dist[u] + line[v].w;
				Q.push(make_pair(dist[line[v].v], line[v].v));
			}
		}
	}
	if(dist[m] == 0x3f3f3f3f) return dist[m];
	return dist[m] * (t - s + 1);
}
int main()
{
	int i, j, u, v, w;
	scanf("%d%d%d%d", &n, &m, &k, &e);
	for(i = 1; i < 2 * e; i += 2)
	{
		scanf("%d%d%d", &u, &v, &w);
		line[i].v = v; line[i].next = head[u]; head[u] = i;
		line[i + 1].v = u; line[i + 1].next = head[v]; head[v] = i + 1;
		line[i].w = line[i + 1].w = w;
	}
	scanf("%d", &d);
	for(i = 0; i < d; ++i)
	{
		scanf("%d%d%d", &u, &v, &w);
		while(v <= w) flag[u][v++] = true;
	}
	for(i = 1; i <= n; ++i)
	{
		f[i] = shortest(1, i);
		for(j = 1; j < i; ++j) f[i] = min(f[i], f[j] + shortest(j + 1, i) + k);
	}
	printf("%d\n", f[n]);
	return 0;
}
