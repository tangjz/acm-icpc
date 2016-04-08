#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 20001, maxm = 100001, maxq = 5001;
int t, n, m, q, fa[maxn], sz[maxn], sum, ans[maxq];
struct Edge
{
	int u, v, w;
	bool operator < (const Edge &t) const
	{
		return w < t.w;
	}
} e[maxm];
struct Query
{
	int id, w;
	bool operator < (const Query &t) const
	{
		return w < t.w;
	}
} que[maxq];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &m, &q);
		for(int i = 1; i <= n; ++i)
		{
			fa[i] = i;
			sz[i] = 1;
		}
		for(int i = 0; i < m; ++i)
			scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		for(int i = 0; i < q; ++i)
		{
			que[i].id = i;
			scanf("%d", &que[i].w);
		}
		sort(e, e + m);
		sort(que, que + q);
		sum = 0;
		for(int i = 0, j = 0; i < q; ++i)
		{
			for( ; j < m && e[j].w <= que[i].w; ++j)
			{
				int u = e[j].u, v = e[j].v;
				if((u = find(u)) != (v = find(v)))
				{
					sum += sz[u] * sz[v];
					fa[u] = v;
					sz[v] += sz[u];
				}
			}
			ans[que[i].id] = sum;
		}
		for(int i = 0; i < q; ++i)
			printf("%d\n", ans[i] * 2);
	}
	return 0;
}
