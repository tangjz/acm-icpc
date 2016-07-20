#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxs = 101, maxn = 10010, maxm = 60010, d[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}, INF = maxn << 2;
int t, n, m, dx, dy, N, M, S, T, col[maxn], deg[maxn], lnk[maxn], cur[maxn], level[maxn], que[maxn], L, R, out[maxn];
struct Edge
{
	int nxt, v, f;
} e[maxm << 1];
char str[maxs];
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
	int ret = 0, tmp;
	for(int &it = cur[u]; it != -1; it = e[it].nxt)
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
void check(int u, int o)
{
	out[u] = o;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(out[e[it].v] == -1 && e[it ^ o].f)
			check(e[it].v, o);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		int ans = 0;
		scanf("%d%d%d%d", &n, &m, &dx, &dy);
		N = n * m + 2;
		M = 0;
		S = N - 2;
		T = N - 1;
		memset(col, -1, N * sizeof(int));
		memset(deg, 0, N * sizeof(int));
		memset(lnk, -1, N * sizeof(int));
		memset(out, -1, N * sizeof(int));
		for(int i = 0, idx = 0; i < n; ++i)
		{
			scanf("%s", str);
			for(int j = 0; j < m; ++j, ++idx)
			{
				if(col[idx] == -1)
				{
					L = R = 0;
					col[idx] = 0;
					que[R++] = idx;
					while(L < R)
					{
						int ldx = que[L++], lx = ldx / m, ly = ldx % m;
						for(int o = 0; o < 4; ++o)
						{
							int rx = lx + d[o][0] * dx, ry = ly + d[o][1] * dy, rdx = rx * m + ry;
							if(rx < 0 || rx >= n || ry < 0 || ry >= m)
								continue;
							addEdge(ldx, rdx, 2);
							++deg[ldx];
							ans += 2;
							if(col[rdx] == -1)
							{
								col[rdx] = col[ldx] ^ 1;
								que[R++] = rdx;
							}
						}
					}
				}
				if(str[j] == '.')
				{
					addEdge(S, idx, deg[idx]);
					addEdge(idx, T, deg[idx]);
				}
				else
				{
					addEdge(S, idx, (str[j] == 'B') == col[idx] ? deg[idx] : INF);
					addEdge(idx, T, (str[j] == 'W') == col[idx] ? deg[idx] : INF);
				}
			}
		}
		while(bfs())
		{
			memcpy(cur, lnk, N * sizeof(int));
			for(int tmp; (tmp = dfs(S, INF)); ans -= tmp);
		}
		printf("%d\n", ans >> 1);
		check(S, 0);
		check(T, 1);
		for(int i = 0, idx = 0; i < n; ++i)
		{
			for(int j = 0; j < m; ++j, ++idx)
			{
				if(out[idx] == -1)
					check(idx, col[idx]);
				str[j] = out[idx] == col[idx] ? 'B' : 'W';
			}
			str[m] = '\0';
			puts(str);
		}
	}
	return 0;
}
