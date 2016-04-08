#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5001, maxm = 5001, maxq = 1000001, INF = 0x3f3f3f3f;
int n, m, q, tot, pre[maxn], que[maxn << 1], L, R, dis[maxn][2], ans[maxq];
struct Edge
{
	int nxt, v;
} e[maxm << 1];
struct Query
{
	int id, s, t, d;
	bool operator < (const Query &x) const
	{
		return s < x.s;
	}
} Q[maxq];
void scan(int &x)
{
	static int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
int main()
{
	scan(n), scan(m), scan(q);
	for(int i = 1, u, v; i <= m; ++i)
	{
		scan(u), scan(v);
		e[++tot] = (Edge){pre[u], v};
		pre[u] = tot;
		e[++tot] = (Edge){pre[v], u};
		pre[v] = tot;
	}
	for(int i = 0; i < q; ++i)
	{
		Q[i].id = i;
		scan(Q[i].s), scan(Q[i].t), scan(Q[i].d);
		if(Q[i].s > Q[i].t)
			swap(Q[i].s, Q[i].t);
	}
	sort(Q, Q + q);
	for(int i = 1, j = 0; i <= n && j < q; ++i)
	{
		if(Q[j].s > i)
			continue;
		L = R = 0;
		memset(dis, 0x3f, sizeof dis);
		que[R++] = i << 1;
		dis[i][0] = 0;
		while(L < R)
		{
			int u = que[L++], o = u & 1;
			u >>= 1;
			for(int it = pre[u]; it; it = e[it].nxt)
				if(dis[e[it].v][o ^ 1] == INF)
				{
					dis[e[it].v][o ^ 1] = dis[u][o] + 1;
					que[R++] = (e[it].v << 1) | (o ^ 1);
				}
		}
		for( ; j < q && Q[j].s == i; ++j)
			if(i != Q[j].t || pre[i])
				ans[Q[j].id] = dis[Q[j].t][Q[j].d & 1] <= Q[j].d;
			else
				ans[Q[j].id] = !Q[j].d;
	}
	for(int i = 0; i < q; ++i)
		puts(ans[i] ? "TAK" : "NIE");
	return 0;
}
