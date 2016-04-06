#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int INF = 60;
class MinCost_MaxFlow
{
private:
	struct Edge { int to, cap, flow, nxt; } edges[23333];
	int n, m, s, t, flow, G[10010], level[10010];
	void AddEdge(int from, int to, int cap)
	{
		edges[m] = (Edge){to, cap, 0, G[from]};
		G[from] = m++;
		edges[m] = (Edge){from, 0, 0, G[to]};
		G[to] = m++;
	}
	int Q[10010];
	bool bfs()
	{
		int head = 0, tail = -1;
		memset(level, 0, sizeof(level));
		level[s] = 1;
		Q[++tail] = s;
		while(head <= tail)
		{
			int u = Q[head++];
			for(int i = G[u]; i != -1; i = edges[i].nxt)
			{
				Edge &e = edges[i];
				if(e.cap > e.flow && !level[e.to])
				{
					level[e.to] = level[u] + 1;
					Q[++tail] = e.to;
				}
			}
		}
		return level[t];
	}
	int dfs(int u, int alpha)
	{
		if(u == t || !alpha) return alpha;
		int w = 0, k;
		for(int i = G[u]; i != -1; i = edges[i].nxt)
		{
			Edge &e = edges[i];
			if(e.cap > e.flow && level[e.to] == level[u] + 1 && (k = dfs(e.to, min(e.cap - e.flow, alpha - w))))
			{
				e.flow += k;
				edges[i ^ 1].flow -= k;
				w += k;
			}
		}
		return w;
	}
	void MaxFlow()
	{
		int Flow;
		while(bfs())
			while((Flow = dfs(s, INF)))
				flow += Flow;
	}
public:
	int a[110], c[110], d[110][10][2];
	int solve()
	{
		memset(G, -1, sizeof(G));
		m = flow = 0;
		int N, M, i, j, k;
		scanf("%d%d", &N, &M);
		s = N * 9, t = N * 9 + 1;
		for(i = 0; i < N; ++i)
		{
			scanf("%d", &a[i]);
			for(j = 2, k = a[i]; (long long)j * j <= k; ++j)
				if(k % j == 0)
				{
					d[i][c[i]][0] = j;
					while(k % j == 0)
					{
						++d[i][c[i]][1];
						k /= j;
					}
					if(i & 1)
						AddEdge(s, i * 9 + c[i], d[i][c[i]][1]);
					else
						AddEdge(i * 9 + c[i], t, d[i][c[i]][1]);
					++c[i];
				}
			if(k > 1)
			{
				d[i][c[i]][0] = k;
				++d[i][c[i]][1];
				if(i & 1)
					AddEdge(s, i * 9 + c[i], d[i][c[i]][1]);
				else
					AddEdge(i * 9 + c[i], t, d[i][c[i]][1]);
				++c[i];
			}
		}
		while(M--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			--x, --y;
			if(y & 1)
				swap(x, y);
			for(i = 0; i < c[x]; ++i)
				for(j = 0; j < c[y]; ++j)
					if(d[x][i][0] == d[y][j][0])
						AddEdge(x * 9 + i, y * 9 + j, INF);
		}
		MaxFlow();
		return flow;
	}
} NetWork;
int main()
{
	printf("%d\n", NetWork.solve());
}
