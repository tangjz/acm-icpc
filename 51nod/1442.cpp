#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 210, maxm = 710, INF = 0x3f3f3f3f;
int N, M, S, T, lnk[maxn], cur[maxn], level[maxn], que[maxn];
struct Edge
{
	int nxt, v, f;
} e[maxm << 1];
void addEdge(int u, int v, int c)
{
	if(!c)
		return;
	e[M] = (Edge){lnk[u], v, c};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0};
	lnk[v] = M++;
}
bool bfs()
{
	int L = 0, R = 0;
	memset(level, 0, N * sizeof(int));
	level[S] = 1;
	que[R++] = S;
	while(L < R)
	{
		int u = que[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].f && !level[e[it].v])
			{
				level[e[it].v] = level[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return level[T];
}
int dfs(int u, int lim)
{
	if(u == T || !lim)
		return lim;
	int ret = 0;
	for(int &it = cur[u], tmp; it != -1; it = e[it].nxt)
		if(e[it].f && level[e[it].v] == level[u] + 1
		&& (tmp = dfs(e[it].v, std::min(e[it].f, lim - ret))))
		{
			e[it].f -= tmp;
			e[it ^ 1].f += tmp;
			if((ret += tmp) == lim)
				break;
		}
	if(!ret)
		level[u] = 0;
	return ret;
}
int n, m, a[maxn], b[maxn];
std::vector<int> g[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int i = 0; i < n; ++i)
		scanf("%d", b + i);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[--u].push_back(--v);
		g[v].push_back(u);
	}
	N = n * 2 + 2;
	M = 0;
	S = N - 2;
	T = N - 1;
	memset(lnk, -1, N * sizeof(int));
	for(int i = 0; i < n; ++i)
	{
		addEdge(S, i, a[i]);
		addEdge(i, n + i, INF);
		addEdge(n + i, T, b[i]);
		for(std::vector<int>::iterator it = g[i].begin(); it != g[i].end(); ++it)
			addEdge(i, n + (*it), INF);
	}
	while(bfs())
	{
		memcpy(cur, lnk, N * sizeof(int));
		for(int tmp; (tmp = dfs(S, INF)); );
	}
	bool flag = 0;
	for(int it = lnk[S]; it != -1; it = e[it].nxt)
		if(e[it].v < n && e[it].f)
		{
			flag = 1;
			break;
		}
	for(int i = 0; i < n && !flag; ++i)
		for(int it = lnk[n + i]; it != -1; it = e[it].nxt)
			if(e[it].v == T && e[it].f)
			{
				flag = 1;
				break;
			}
	puts(!flag ? "YES" : "NO");
	return 0;
}
