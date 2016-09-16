#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 61, maxm = maxn << 2, INF = 0x3f3f3f3f;
int N, M, S, T, lnk[maxn], cur[maxn], level[maxn], que[maxn];
struct Edge
{
	int nxt, v, f;
} e[maxm << 1];
void addEdge(int u, int v, int c)
{
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
	for(int it = cur[u], tmp; it != -1; it = e[it].nxt)
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
int n, a[maxn], fa[2][maxn], idx, ans;
std::vector<int> g[2][maxn];
void pfs(int u, int fro)
{
	for(std::vector<int>::iterator it = g[idx][u].begin(); it != g[idx][u].end(); ++it)
		if((*it) != fro)
		{
			fa[idx][*it] = u;
			pfs(*it, u);
		}
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int t = 0; t < 2; ++t)
		for(int i = 1; i < n; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			g[t][u].push_back(v);
			g[t][v].push_back(u);
		}
	for(int rt = 0; rt < n; ++rt)
	{
		for(int t = 0; t < 2; ++t)
		{
			pfs(rt, fa[idx][rt] = -1);
			idx ^= 1;
		}
		N = n + 2;
		M = 0;
		S = N - 2;
		T = N - 1;
		memset(lnk, -1, N * sizeof(int));		
		int sum = 0;
		for(int i = 0; i < n; ++i)
		{
			if(a[i] > 0)
			{
				sum += a[i];
				addEdge(S, i, a[i]);
			}
			else if(a[i] < 0)
				addEdge(i, T, -a[i]);
			for(int t = 0; t < 2; ++t)
				if(fa[t][i] != -1)
					addEdge(i, fa[t][i], INF);
		}
		int flow = 0;
		while(bfs())
		{
			memcpy(cur, lnk, N * sizeof(int));
			for(int tmp; (tmp = dfs(S, INF)); flow += tmp);
		}
		if(ans < sum - flow)
			ans = sum - flow;
	}
	printf("%d\n", ans);
	return 0;
}
