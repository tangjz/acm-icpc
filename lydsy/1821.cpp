#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1001;
int n, m, tot, x[maxn], y[maxn], fa[maxn];
struct Edge
{
	int u, v, w;
	bool operator < (const Edge &t) const
	{
		return w < t.w;
	}
} e[maxn * maxn >> 1];
int sqr(int x)
{
	return x * x;
}
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", x + i, y + i);
		fa[i] = i;
		for(int j = 0; j < i; ++j)
			e[tot++] = (Edge){i, j, sqr(x[i] - x[j]) + sqr(y[i] - y[j])};
	}
	sort(e, e + tot);
	for(int i = 0; i < tot; ++i)
		if(find(e[i].u) != find(e[i].v))
		{
			if(n > m)
			{
				fa[find(e[i].u)] = find(e[i].v);
				--n;
			}
			else
			{
				printf("%.2f\n", sqrt(e[i].w));
				break;
			}
		}
	return 0;
}
