#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2001, maxm = 10001;
int n, m, fa[maxn], ans;
struct Edge
{
	int u, v, w;
	bool operator < (const Edge &x) const
	{
		return w < x.w;
	}
} e[maxm];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	sort(e, e + m);
	for(int i = 1; i <= n; ++i)
		fa[i] = i;
	for(int i = 0; i < m; ++i)
		if(find(e[i].u) != find(e[i].v))
		{
			fa[find(e[i].u)] = find(e[i].v);
			ans = e[i].w;
		}
	printf("%d\n", ans);
	return 0;
}
