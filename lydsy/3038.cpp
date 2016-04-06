#include <cmath>
#include <cstdio>
const int maxn = 100001;
int n, m, fa[maxn];
long long a[maxn], bit[maxn];
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
void add(int x, long long v)
{
	for( ; x < n; x += ~x & x + 1)
		bit[x] += v;
}
long long sum(int x)
{
	long long ret = 0;
	for( ; x >= 0; x -= ~x & x + 1)
		ret += bit[x];
	return ret;
}
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%lld", a + i);
		add(i, a[i]);
		fa[i] = i;
	}
	fa[n] = n;
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i)
	{
		int k, l, r;
		scanf("%d%d%d", &k, &l, &r);
		if(--l > --r)
			swap(l, r);
		if(k == 1)
			printf("%lld\n", sum(r) - sum(l - 1));
		else
			for(int j = find(l); j <= r; j = find(j + 1))
			{
				long long x = sqrt(a[j]);
				add(j, x - a[j]);
				a[j] = x;
				if(a[j] == 1)
					fa[j] = find(j + 1);
			}
	}
	return 0;
}
