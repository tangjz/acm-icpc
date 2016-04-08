#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int t, n, m, tot, a[maxn][maxn], fa[maxn * maxn], ans;
struct Edge
{
	int u, v, w;
	bool operator < (const Edge &x) const
	{
		return w < x.w;
	}
} e[maxn * maxn * 4];
void addedge(int u, int v, int w)
{
	e[tot++] = (Edge){u, v, w};
}
int idx(int x, int y)
{
	return x * m + y;
}
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		ans = tot = 0;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
			{
				scanf("%d", &a[i][j]);
				if(i > 0)
					addedge(idx(i, j), idx(i - 1, j), abs(a[i][j] - a[i - 1][j]));
				if(j > 0)
					addedge(idx(i, j), idx(i, j - 1), abs(a[i][j] - a[i][j - 1]));
			}
		for(int i = 0; i < n * m; ++i)
			fa[i] = i;
		sort(e, e + tot);
		for(int i = 0; i < tot; ++i)
		{
			int u = find(e[i].u), v = find(e[i].v);
			if(u != v)
			{
				fa[u] = v;
				ans += e[i].w;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
