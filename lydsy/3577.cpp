#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 61, maxd = 6, maxm = 10001;
const int maxN = maxn * maxn * maxd * 2 + maxm * 2, maxM = maxN * 5, INF = 0x3f3f3f3f;
int n, m, a, b, in[maxd][maxn][maxn], out[maxd][maxn][maxn], Log[maxn];
int N, M, S, T, lnk[maxN], cur[maxN], level[maxN], que[maxN], L, R;
struct Edge
{
	int nxt, v, f;
} e[maxM << 1];
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
			if(!level[e[it].v] && e[it].f)
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
		if(level[e[it].v] == level[u] + 1
		&& (tmp = dfs(e[it].v, std::min(lim - ret, e[it].f))))
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
int main()
{
	scanf("%d%d%d%d", &n, &m, &a, &b);
	memset(lnk, -1, sizeof lnk);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
		{
			int w;
			scanf("%d", &w);
			in[0][i][j] = N++;
			out[0][i][j] = N++;
			addEdge(in[0][i][j], out[0][i][j], w);
		}
	for(int d = 1; 1 << d <= n && 1 << d <= m; ++d)
		for(int i = 0; i + (1 << d) <= n; ++i)
			for(int j = 0; j + (1 << d) <= m; ++j)
			{
				in[d][i][j] = N++;
				addEdge(in[d][i][j], in[d - 1][i][j], INF);
				addEdge(in[d][i][j], in[d - 1][i][j + (1 << d - 1)], INF);
				addEdge(in[d][i][j], in[d - 1][i + (1 << d - 1)][j], INF);
				addEdge(in[d][i][j], in[d - 1][i + (1 << d - 1)][j + (1 << d - 1)], INF);
				out[d][i][j] = N++;
				addEdge(out[d - 1][i][j], out[d][i][j], INF);
				addEdge(out[d - 1][i][j + (1 << d - 1)], out[d][i][j], INF);
				addEdge(out[d - 1][i + (1 << d - 1)][j], out[d][i][j], INF);
				addEdge(out[d - 1][i + (1 << d - 1)][j + (1 << d - 1)], out[d][i][j], INF);
			}
	for(int i = 2; i <= n && i <= m; ++i)
		Log[i] = Log[i >> 1] + 1;
	S = N++;
	while(a--)
	{
		int w, x1, y1, x2, y2;
		scanf("%d%d%d%d%d", &w, &x1, &y1, &x2, &y2);
		--x1, --y1, --x2, --y2;
		int d = Log[x2 - x1 + 1], idx = N++;
		addEdge(S, idx, w);
		addEdge(idx, in[d][x1][y1], INF);
		addEdge(idx, in[d][x1][y2 - (1 << d) + 1], INF);
		addEdge(idx, in[d][x2 - (1 << d) + 1][y1], INF);
		addEdge(idx, in[d][x2 - (1 << d) + 1][y2 - (1 << d) + 1], INF);
	}
	T = N++;
	while(b--)
	{
		int w, x1, y1, x2, y2;
		scanf("%d%d%d%d%d", &w, &x1, &y1, &x2, &y2);
		--x1, --y1, --x2, --y2;
		int d = Log[x2 - x1 + 1], idx = N++;
		addEdge(idx, T, w);
		addEdge(out[d][x1][y1], idx, INF);
		addEdge(out[d][x1][y2 - (1 << d) + 1], idx, INF);
		addEdge(out[d][x2 - (1 << d) + 1][y1], idx, INF);
		addEdge(out[d][x2 - (1 << d) + 1][y2 - (1 << d) + 1], idx, INF);
	}
	int flow = 0;
	while(bfs())
	{
		memcpy(cur, lnk, N * sizeof(int));
		for(int tmp; (tmp = dfs(S, INF)); flow += tmp);
	}
	printf("%d\n", flow);
	return 0;
}
