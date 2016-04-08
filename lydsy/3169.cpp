#include <cstdio>
const int maxn = 100001, maxm = 1000001;
int n, m, typ[maxn], tot, pre[maxn], deg[maxn], que[2][maxn], L[2], R[2];
struct Edge
{
	int nxt, v;
} e[maxm];
int calc(int now)
{
	int ret = 0;
	for(int it = 1; it <= tot; ++it)
		++deg[e[it].v];
	L[0] = L[1] = R[0] = R[1] = 0;
	for(int i = 0; i < n; ++i)
		if(!deg[i])
			que[typ[i]][R[typ[i]]++] = i;
	for(int i = now; ; i ^= 1, ++ret)
	{
		while(L[i] < R[i])
		{
			int &u = que[i][L[i]++];
			for(int it = pre[u]; it; it = e[it].nxt)
				if(!(--deg[e[it].v]))
					que[typ[e[it].v]][R[typ[e[it].v]]++] = e[it].v;
		}
		if(L[0] == R[0] && L[1] == R[1])
			break;
	}
	return ret;
}
int min(int x, int y)
{
	return x < y ? x : y;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", typ + i);
		--typ[i];
	}
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){pre[--u], --v};
		pre[u] = tot;
	}
	printf("%d\n", min(calc(0), calc(1)));
	return 0;
}
