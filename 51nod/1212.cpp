#include <stdio.h>
#include <algorithm>
const int maxn = 1001, maxm = 50001;
int n, m, fa[maxn], ans;
std::pair<int, std::pair<int, int> > e[maxm];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		scanf("%d%d%d", &e[i].second.first, &e[i].second.second, &e[i].first);
	std::sort(e, e + m);
	for(int i = 1; i <= n; ++i)
		fa[i] = i;
	for(int i = 0; i < m; ++i)
	{
		int u = find(e[i].second.first), v = find(e[i].second.second);
		if(u != v)
		{
			fa[u] = v;
			ans += e[i].first;
		}
	}
	printf("%d\n", ans);
	return 0;
}
