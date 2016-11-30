#include <cstdio>
#include <cstring>
const int maxn = 10001, maxm = 100001;
int n, m, q, tot, lnk[maxn], pre[maxn], dsu[maxn];
struct Edge
{
	int nxt, v;
} e[maxm << 1];
int find(int u)
{
	return dsu[u] < 0 ? u : dsu[u] = find(dsu[u]);
}
void merge(int u, int v)
{
	if((u = find(u)) == (v = find(v)))
		return;
	if(dsu[u] < dsu[v])
		dsu[v] = u;
	else if(dsu[u] > dsu[v])
		dsu[u] = v;
	else
	{
		dsu[v] = u;
		--dsu[u];
	}
}
int tarjan(int u, int pid)
{
	int lowu = pre[u] = tot++;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		if(it == pid)
			continue;
		int v = e[it].v;
		if(pre[v] == -1)
		{
			int lowv = tarjan(v, it ^ 1);
			if(lowu > lowv)
				lowu = lowv;
			if(pre[u] < lowv)
				merge(u, v);
		}
		else if(lowu > pre[v])
			lowu = pre[v];
	}
	return lowu;
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &q) == 3 && n + m + q)
	{
		tot = 0;
		memset(lnk + 1, -1, n * sizeof(int));
		memset(pre + 1, -1, n * sizeof(int));
		memset(dsu + 1, -1, n * sizeof(int));
		while(m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[tot] = (Edge){lnk[u], v};
			lnk[u] = tot++;
			e[tot] = (Edge){lnk[v], u};
			lnk[v] = tot++;
		}
		for(int i = 1; i <= n; ++i)
			if(pre[i] == -1)
				tarjan(i, -1);
		while(q--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			putchar(find(u) == find(v) ? 'Y' : 'N');
			putchar('\n');
		}
		putchar('-');
		putchar('\n');
	}
	return 0;
}
