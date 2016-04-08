#include <cstdio>
#include <cstring>
const int maxn = 1010, maxm = 12010, INF = 0x3f3f3f3f;
class MinCost_MaxFlow
{
private:
	struct Edge
	{
		int nxt, u, v, flow, cost;
	} edges[maxm << 1];
	int n, m, g[maxn], d[maxn], p[maxn], a[maxn];
	bool inq[maxm << 1];
	void AddEdge(int u, int v, int flow, int cost)
	{
		edges[m] = (Edge){g[u], u, v, flow, cost};
		g[u] = m++;
		edges[m] = (Edge){g[v], v, u, 0, -cost};
		g[v] = m++;
	}
	bool BellmanFord(int s, int t, int &flow, int &cost)
	{
		static int que[maxn], L, R;
		L = 0, R = 0;
		memset(d, 0x3f, sizeof d);
		memset(inq, 0, sizeof inq);
		que[R++] = s;
		d[s] = p[s] = 0;
		a[s] = INF;
		inq[s] = 1;
		while(L != R)
		{
			int u = que[L++];
			if(L == maxn)
				L = 0;
			inq[u] = 0;
			for(int it = g[u]; it != -1; it = edges[it].nxt)
			{
				Edge &e = edges[it];
				if(e.flow && d[e.v] > d[u] + e.cost)
				{
					d[e.v] = d[u] + e.cost;
					p[e.v] = it;
					a[e.v] = a[u] < e.flow ? a[u] : e.flow;
					if(!inq[e.v])
					{
						que[R++] = e.v;
						if(R == maxn)
							R = 0;
						inq[e.v] = 1;
					}
				}
			}
		}
		if(d[t] == INF)
			return 0;
		flow += a[t];
		cost += d[t] * a[t];
		for(int u = t; u != s; u = edges[p[u]].u)
		{
			edges[p[u]].flow -= a[t];
			edges[p[u] ^ 1].flow += a[t];
		}
		return 1;
	}
public:
	int MinCost(int s, int t)
	{
		int flow = 0, cost = 0;
		while(BellmanFord(s, t, flow, cost));
		return cost;
	}
	void solve(int N, int M)
	{
		static int A[maxn], s, t;
		n = N + 3, m = 0;
		s = 0, t = N + 2;
		memset(g, -1, sizeof g);
		for(int i = 1; i <= N; ++i)
			scanf("%d", A + i);
		A[0] = A[N + 1] = 0;
		for(int i = 1; i <= N + 1; ++i)
		{
			int res = A[i] - A[i - 1];
			if(res >= 0)
				AddEdge(s, i, res, 0);
			else
				AddEdge(i, t, -res, 0);
			if(i > 1)
				AddEdge(i, i - 1, INF, 0);
		}
		for(int i = 1; i <= M; ++i)
		{
			int S, T, C;
			scanf("%d%d%d", &S, &T, &C);
			AddEdge(S, T + 1, INF, C);
		}
		printf("%d\n", MinCost(s, t));
	}
} NetWork;

int main()
{
	int n, m;
	while(scanf("%d%d", &n, &m) == 2)
		NetWork.solve(n, m);
	return 0;
}
