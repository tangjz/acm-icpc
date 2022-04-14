#include <stdio.h>
#include <cstring>
#include <unordered_map>
const int maxn = 100001;
int n, a[maxn], p, q, dsu[maxn];
std::unordered_map<int, int> idx;
int dsu_find(int x)
{
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v)
{
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] > dsu[v])
		std::swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[u];
	dsu[v] = u;
}
int main()
{
	scanf("%d%d%d", &n, &p, &q);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		idx[a[i]] = i;
	}
	memset(dsu, -1, (n + 2) * sizeof(int));
	for(int i = 0; i < n; ++i)
	{
		if(idx.count(p - a[i]))
			dsu_merge(i, idx[p - a[i]]);
		else
			dsu_merge(i, n + 1);
		if(idx.count(q - a[i]))
			dsu_merge(i, idx[q - a[i]]);
		else
			dsu_merge(i, n);
	}
	if(dsu_find(n) != dsu_find(n + 1))
	{
		puts("YES");
		for(int i = 0; i < n; ++i)
			printf("%d%c", dsu_find(i) == dsu_find(n + 1), " \n"[i == n - 1]);
	}
	else
		puts("NO");
	return 0;
}