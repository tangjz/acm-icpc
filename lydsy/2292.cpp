#include <cstdio>
const int maxn = 1100001, maxm = 1000001;
int t, n, m, tot, pre[maxn], que[maxn], L, R, dis[maxn];
struct Edge
{
	int nxt, v;
} e[maxm << 1];
void AddEdge(int u, int v)
{
	e[++tot] = (Edge){pre[u], v};
	pre[u] = tot;
}
int main()
{
	scanf("%d%d", &n, &m);
	t = n;
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(w == 1)
			AddEdge(u, v);
		else
		{
			AddEdge(u, ++n);
			AddEdge(n, v);
		}
	}
	que[R++] = 1;
	dis[1] = 1;
	while(L < R)
	{
		int &u = que[L++];
		for(int it = pre[u]; it; it = e[it].nxt)
			if(!dis[e[it].v])
			{
				dis[e[it].v] = dis[u] + 1;
				que[R++] = e[it].v;
			}
	}
	printf("%d\n", dis[t] - dis[1]);
	return 0;
}
