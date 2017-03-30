#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100003;
int n, a[maxn], p, q, dsu[maxn];
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
		scanf("%d", a + i);
	std::sort(a, a + n);
	bool flag = 1;
	memset(dsu, -1, (n + 2) * sizeof(int));
	for(int i = 0, j = n - 1, k = n - 1; i < n && flag; ++i)
	{
		for( ; j >= 0 && a[i] + a[j] > p; --j);
		for( ; k >= 0 && a[i] + a[k] > q; --k);
		bool f1 = j >= 0 && a[i] + a[j] == p;
		bool f2 = k >= 0 && a[i] + a[k] == q;
		if(f1 != f2)
		{
			dsu_merge(i, n + !f1);
			dsu_merge(i, f1 ? j : k);
		}
		else
			flag &= f1;
	}
	flag &= dsu_find(n) != dsu_find(n + 1);
	puts(flag ? "YES" : "NO");
	return 0;
}
