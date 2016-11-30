#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 210, maxm = maxn * maxn << 1, INF = 0x3f3f3f3f;
int N, M, S, T, lnk[maxn], level[maxn], que[maxn], L, R;
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
			if((ret += tmp) == lim)
				break;
		}
	if(!ret)
		level[u] = 0;
	return ret;
}
int t, n, m, l[maxn], r[maxn], q[maxn], totx, quex[maxn], toty, quey[maxn];
bool ban[maxn][maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		totx = toty = 0;
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d%d", l + i, r + i, q + i);
			quex[totx++] = l[i];
			quex[totx++] = r[i] + 1;
			quey[toty++] = q[i];
			quey[toty++] = q[i] + 1;
		}
		quex[totx++] = 1;
		quex[totx++] = n + 1;
		quey[toty++] = 1;
		quey[toty++] = n + 1;
		sort(quex, quex + totx);
		totx = unique(quex, quex + totx) - quex;
		sort(quey, quey + toty);
		toty = unique(quey, quey + toty) - quey;
		memset(ban, 0, sizeof ban);
		for(int i = 0; i < m; ++i)
		{
			l[i] = lower_bound(quex, quex + totx, l[i]) - quex;
			r[i] = lower_bound(quex, quex + totx, r[i] + 1) - quex;
			q[i] = lower_bound(quey, quey + toty, q[i]) - quey;
			for(int j = 0; j < totx - 1; ++j)
				if(l[i] <= j && j < r[i])
					for(int k = q[i] + 1; k < toty - 1; ++k)
						ban[j][k] = 1;
				else
					ban[j][q[i]] = 1;
		}
		N = totx + toty + 2;
		M = 0;
		S = N - 2;
		T = N - 1;
		memset(lnk, -1, N * sizeof(int));
		for(int i = 0; i < totx - 1; ++i)
		{
			addEdge(S, i, quex[i + 1] - quex[i]);
			for(int j = 0; j < toty - 1; ++j)
				if(!ban[i][j])
					addEdge(i, totx + j, INF);
		}
		for(int i = 0; i < toty - 1; ++i)
			addEdge(totx + i, T, quey[i + 1] - quey[i]);
		int flow = 0;
		while(bfs())
			for(int tmp; (tmp = dfs(S, INF)); flow += tmp);
		puts(flow == n ? "Possible" : "Impossible");
	}
	return 0;
}
