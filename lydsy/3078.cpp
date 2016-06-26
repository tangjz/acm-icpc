#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxs = 101, maxn = maxs * maxs, maxm = maxn * 3;
int n, m, N, M, S, T, lnk[maxn], level[maxn], que[maxn], L, R;
char str[maxs][maxs];
struct Edge
{
	int nxt, v, f;
} e[maxm << 1];
inline int tidx(int x, int y)
{
	return x * m + y;
}
inline void ridx(int o, int &x, int &y)
{
	x = o / m;
	y = o % m;
}
void addEdge(int u, int v, int c)
{
	e[M] = (Edge){lnk[u], v, c};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0};
	lnk[v] = M++;
}
bool bfs()
{
	L = R = 0;
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
	for(int it = lnk[u], tmp; it != -1; it = e[it].nxt)
		if(e[it].f && level[e[it].v] == level[u] + 1
		&& (tmp = dfs(e[it].v, std::min(e[it].f, lim - ret))))
		{
			e[it].f -= tmp;
			e[it ^ 1].f += tmp;
			ret += tmp;
		}
	if(!ret)
		level[u] = 0;
	return ret;
}
bool vis[maxn];
void check(int u, int o)
{
	vis[u] = 1;
	if(u < n * m)
	{
		int x, y;
		ridx(u, x, y);
		if(((x & 1) ^ (y & 1)) == o)
			str[x][y] = 'B';
	}
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(e[it ^ o].f && !vis[e[it].v])
			check(e[it].v, o);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		int cL = 0, cR = 0;
		N = n * m + 2;
		M = 0;
		S = N - 2;
		T = N - 1;
		memset(lnk, -1, N * sizeof(int));
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", str[i]);
			for(int j = 0; j < m; ++j)
			{
				if(str[i][j] == 'X')
					continue;
				str[i][j] = 'A';
				if((i & 1) == (j & 1))
				{
					++cL;
					addEdge(S, tidx(i, j), 1);
					if(i > 0 && str[i - 1][j] != 'X')
						addEdge(tidx(i, j), tidx(i - 1, j), 1);
					if(j > 0 && str[i][j - 1] != 'X')
						addEdge(tidx(i, j), tidx(i, j - 1), 1);
				}
				else
				{
					++cR;
					addEdge(tidx(i, j), T, 1);
					if(i > 0 && str[i - 1][j] != 'X')
						addEdge(tidx(i - 1, j), tidx(i, j), 1);
					if(j > 0 && str[i][j - 1] != 'X')
						addEdge(tidx(i, j - 1), tidx(i, j), 1);
				}
			}
		}
		while(bfs())
			while(dfs(S, maxn));
		memset(vis, 0, N * sizeof(bool));
		check(S, 0);
		memset(vis, 0, N * sizeof(bool));
		check(T, 1);
		for(int i = 0; i < n; ++i)
			puts(str[i]);
		putchar('\n');
	}
	return 0;
}
