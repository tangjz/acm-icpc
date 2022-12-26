#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 40011, maxm = 400011, INF = 0x3f3f3f3f;
int N, M, S, T, lnk[maxn], cur[maxn], lev[maxn];
struct Edge {
	int nxt, v, f;
} e[maxm];
void addEdge(int u, int v, int w)
{
	e[M] = (Edge){lnk[u], v, w};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0};
	lnk[v] = M++;
}
bool bfs()
{
	int L = 0, R = 0;
	static int que[maxn];
	memset(lev, -1, N * sizeof(int));
	lev[S] = 0;
	que[R++] = S;
	while(L < R)
	{
		int u = que[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].f && lev[e[it].v] == -1)
			{
				lev[e[it].v] = lev[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return lev[T] != -1;
}
int dfs(int u, int lim)
{
	if(u == T || !lim)
		return lim;
	int ret = 0, tp;
	for(int &it = cur[u]; it != -1; it = e[it].nxt)
	{
		if(lev[e[it].v] != lev[u] + 1
		|| !(tp = dfs(e[it].v, std::min(lim - ret, e[it].f))))
			continue;
		e[it].f -= tp;
		e[it ^ 1].f += tp;
		if((ret += tp) == lim)
			break;
	}
	if(!ret)
		lev[u] = -1;
	return ret;
}
const int maxs = 201, maxd = 8, dx[maxd] = {1, 2, 2, 1, -1, -2, -2, -1}, dy[maxd] = {2, 1, -1, -2, -2, -1, 1, 2};
int n, m, val[maxs][maxs];
inline int idx(int x, int y)
{
	return x * m + y;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", val[i] + j);
	N = n * m + 2;
	M = 0;
	S = N - 2;
	T = N - 1;
	memset(lnk, -1, N * sizeof(int));
	int ans = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
		{
			if(val[i][j] == 1)
				continue;
			++ans;
			if((i & 1) == (j & 1))
			{
				addEdge(S, idx(i, j), 1);
				for(int d = 0; d < maxd; ++d)
				{
					int u = i + dx[d], v = j + dy[d];
					if(u >= 0 && u < n && v >= 0 && v < m && val[u][v] != 1)
						addEdge(idx(i, j), idx(u, v), 1);
				}
			}
			else
				addEdge(idx(i, j), T, 1);
		}
	while(bfs())
	{
		memcpy(cur, lnk, N * sizeof(int));
		ans -= dfs(S, INF);
	}
	printf("%d\n", ans);
	return 0;
}
