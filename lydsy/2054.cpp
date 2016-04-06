#include <cstdio>
const int maxn = 1000010;
int n, m, p, q, fa[maxn], ans[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &p, &q);
	for(int i = 0; i <= n; ++i)
		fa[i] = i;
	for(int i = m; i > 0; --i)
	{
		int l = (i * p + q) % n, r = (i * q + p) % n;
		if(l > r)
		{
			int t = l;
			l = r;
			r = t;
		}
		for(int j = find(l); j <= r; j = find(j))
		{
			ans[j] = i;
			fa[j] = find(j + 1);
		}
	}
	for(int i = 0; i < n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
