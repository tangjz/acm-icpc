#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxm = 1000001;
typedef long long LL;
int t, n, m, tot, lnk[maxn], dsu[maxn], val[maxm], ord[maxm], que[maxn], L, R, sz[maxn];
struct Edge
{
	int nxt, v;
} e[maxm << 1];
bool vis[maxm];
LL ans1;
long double ans2;
int find(int x)
{
	return dsu[x] < 0 ? x : dsu[x] = find(dsu[x]);
}
bool merge(int u, int v)
{
	if((u = find(u)) == (v = find(v)))
		return 0;
	if(dsu[u] == dsu[v])
	{
		dsu[v] = u;
		--dsu[u];
	}
	else if(dsu[u] < dsu[v])
		dsu[v] = u;
	else
		dsu[u] = v;
	return 1;
}
bool cmp(const int &x, const int &y)
{
	return val[x] < val[y];
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		tot = 0;
		memset(lnk, -1, n * sizeof(int));
		for(int i = 0; i < m; ++i)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			--u;
			--v;
			e[tot] = (Edge){lnk[u], v};
			lnk[u] = tot++;
			e[tot] = (Edge){lnk[v], u};
			lnk[v] = tot++;
			val[i] = w;
			ord[i] = i;
		}
		std::sort(ord, ord + m, cmp);
		ans1 = 0;
		memset(dsu, -1, n * sizeof(int));
		memset(vis, 0, m * sizeof(bool));
		for(int i = 0, j = 1; i < m && j < n; ++i)
			if(merge(e[ord[i] << 1].v, e[ord[i] << 1 | 1].v))
			{
				++j;
				ans1 += val[ord[i]];
				vis[ord[i]] = 1;
			}
		L = R = 0;
		memset(dsu, -1, n * sizeof(int));
		dsu[0] = -2;
		que[R++] = 0;
		while(L < R)
		{
			int u = que[L++];
			for(int it = lnk[u]; it != -1; it = e[it].nxt)
				if(vis[it >> 1] && dsu[e[it].v] == -1)
				{
					dsu[e[it].v] = u;
					que[R++] = e[it].v;
				}
		}
		ans2 = 0.0;
		for(int i = n - 1; i >= 0; --i)
		{
			int u = que[i];
			sz[u] = 1;
			for(int it = lnk[u]; it != -1; it = e[it].nxt)
				if(vis[it >> 1] && dsu[e[it].v] == u)
				{
					ans2 += (LL)val[it >> 1] * sz[e[it].v] * (n - sz[e[it].v]);
					sz[u] += sz[e[it].v];
				}
		}
		printf("%I64d %.2f\n", ans1, (double)(ans2 / (n * (n - 1LL) >> 1)));
	}
	return 0;
}
