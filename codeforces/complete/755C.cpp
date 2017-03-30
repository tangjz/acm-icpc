#include <cstdio>
#include <cstring>
const int maxn = 10001;
int n, dsu[maxn];
int dsu_find(int x)
{
	return dsu[x] < 0 ? x : dsu[x] = dsu_find(dsu[x]);
}
void dsu_merge(int u, int v)
{
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
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
int main()
{
	scanf("%d", &n);
	memset(dsu + 1, -1, n * sizeof(int));
	for(int i = 1; i <= n; ++i)
	{
		int p;
		scanf("%d", &p);
		dsu_merge(i, p);
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		if(dsu_find(i) == i)
			++ans;
	printf("%d\n", ans);
	return 0;
}
