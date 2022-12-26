#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 21000;
int n, m, q, tot;
double ans;
struct point
{
	LL x, y;
} a[maxn], b[maxn], c[maxn];
LL dist(const point &a, const point &b)
{
	return (a.x - b.x) * (a.x - b.x) + (b.y - a.y) * (b.y - a.y);
}
struct edge
{
	int u, v;
	LL w;
	bool operator < (const edge &x) const
	{
		return w < x.w;
	}
} e[maxn * 20];
int fa[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &q) == 3)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%lld%lld", &a[i].x, &a[i].y);
		for(int i = 1; i <= m; ++i)
			scanf("%lld%lld", &b[i].x, &b[i].y);
		for(int i = 1; i <= q; ++i)
			scanf("%lld%lld", &c[i].x, &c[i].y);
		tot = 0;
		for(int i = 1, j = 1; i <= n; ++i)
		{
			while(j < m && b[j].y < a[i].y)
				++j;
			if(i > 1)
				e[tot++] = (edge){i - 1, i, dist(a[i - 1], a[i])};
			if(j > 1)
				e[tot++] = (edge){i, n + j - 1, dist(a[i], b[j - 1])};
			e[tot++] = (edge){i, n + j, dist(a[i], b[j])};
			for(int k = 1; k <= q; ++k)
				e[tot++] = (edge){i, n + m + k, dist(a[i], c[k])};
		}
		for(int i = 1; i <= m; ++i)
		{
			if(i > 1)
				e[tot++] = (edge){n + i - 1, n + i, dist(b[i - 1], b[i])};
			for(int k = 1; k <= q; ++k)
				e[tot++] = (edge){n + i, n + m + k, dist(b[i], c[k])};
		}
		for(int i = 2; i <= q; ++i)
			e[tot++] = (edge){n + m + i - 1, n + m + i, dist(c[i - 1], c[i])};
		sort(e, e + tot);
		n += m + q;
		for(int i = 1; i <= n; ++i)
			fa[i] = i;
		ans = 0;
		for(int i = 0; i < tot; ++i)
			if(find(e[i].u) != find(e[i].v))
			{
				fa[find(e[i].u)] = find(e[i].v);
				ans += sqrt(e[i].w);
			}
		printf("%.6f\n", ans + 1e-10);
	}
	return 0;
}
