#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 60, maxm = 3000, INF = 0x3f3f3f3f;
int tt, n, m, q, tot, deg[maxn], u[maxm], v[maxm];
char str[maxn][21];
class MinCost_MaxFlow
{
private:
	struct Edge { int nxt, from, to, cap, flow, cost; } edges[maxm << 1];
	int N, M, s, t, G[maxn], inq[maxn], d[maxn], p[maxn], a[maxn], que[maxn], l, r;
	void AddEdge(int from, int to, int cap, int cost)
	{
		edges[M] = (Edge){G[from], from, to, cap, 0, cost};
		G[from] = M++;
		edges[M] = (Edge){G[to], to, from, 0, 0, -cost};
		G[to] = M++;
	}
	bool BellmanFord(int &flow, int &cost)
	{
		memset(a, 0, sizeof(a));
		memset(d, 0x3f, sizeof(d));
		memset(inq, 0, sizeof(inq));
		l = r = 0;
		que[r++] = s;
		d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;
		while(l != r)
		{
			int u = que[l++];
			if(l == maxn)
				l = 0;
			inq[u] = 0;
			for(int it = G[u]; it != -1; it = edges[it].nxt)
			{
				Edge &e = edges[it];
				if(e.cap > e.flow && d[u] + e.cost < d[e.to])
				{
					d[e.to] = d[u] + e.cost;
					p[e.to] = it;
					a[e.to] = min(a[u], e.cap - e.flow);
					if(!inq[e.to])
					{
						que[r++] = e.to;
						if(r == maxn)
							r = 0;
						inq[e.to] = 1;
					}
				}
			}
		}
		if(d[t] == INF) return false;
		flow += a[t];
		cost += d[t] * a[t];
		for(int u = t; u != s; u = edges[p[u]].from)
		{
			edges[p[u]].flow += a[t];
			edges[p[u] ^ 1].flow -= a[t];
		}
		return true;
	}
public:
	void init(int lim)
	{
		N = n + 4; M = 0;
		s = n + 2; t = n + 3;
		memset(G, -1, sizeof G);
		for(int i = 0; i < m; ++i)
			AddEdge(v[i], u[i], 1, 1);
		for(int i = 0; i < n; ++i)
		{
			if(deg[i] > 0)
				AddEdge(i, t, deg[i], 0);
			else if(deg[i] < 0)
				AddEdge(s, i, -deg[i], 0);
			AddEdge(n, i, lim, 0);
			AddEdge(i, n + 1, lim, 0);
		}
		AddEdge(n + 1, n, n * lim, 0);
	}
	bool check(int M)
	{
		init(M);
		int flow = 0, cost = 0;
		while(BellmanFord(flow, cost));
		return m - cost >= q;
	}
} NetWork;
int main()
{
	scanf("%d", &tt);
	for(int Case = 1; Case <= tt; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%d%d%d", &n, &m, &q);
		tot = 0;
		memset(deg, 0, sizeof deg);
		for(int i = 0; i < m; ++i)
		{
			char s[21], t[21];
			scanf("%s%s", s, t);
			u[i] = v[i] = -1;
			for(int j = 0; j < tot; ++j)
				if(strcmp(str[j], s) == 0)
				{
					u[i] = j;
					break;
				}
			if(u[i] == -1)
			{
				strcpy(str[tot], s);
				u[i] = tot++;
			}
			for(int j = 0; j < tot; ++j)
				if(strcmp(str[j], t) == 0)
				{
					v[i] = j;
					break;
				}
			if(v[i] == -1)
			{
				strcpy(str[tot], t);
				v[i] = tot++;
			}
			++deg[u[i]];
			--deg[v[i]];
		}
		int L = 0, R = n - 1, M;
		while(L < R)
		{
			M = L + R >> 1;
			if(NetWork.check(M))
				R = M;
			else
				L = M + 1;
		}
		printf("%d\n", L);
	}
	return 0;
}
