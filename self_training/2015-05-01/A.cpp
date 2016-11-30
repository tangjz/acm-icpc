#include <cstdio>
const int maxn = 100010;
int n, m, k, l[maxn], r[maxn], d[maxn], c[maxn];
long long a[maxn];
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i)
		scanf("%I64d", a + i);
	for(int i = n; i; --i)
		a[i] -= a[i - 1];
	for(int i = 1; i <= m; ++i)
		scanf("%d%d%d", l + i, r + i, d + i);
	while(k--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		++c[x];
		--c[y + 1];
	}
	for(int i = 1; i <= m; ++i)
	{
		c[i] += c[i - 1];
		a[l[i]] += (long long)c[i] * d[i];
		a[r[i] + 1] -= (long long)c[i] * d[i];
	}
	for(int i = 1; i <= n; ++i)
	{
		a[i] += a[i - 1];
		printf("%I64d%c", a[i], " \n"[i == n]);
	}
	return 0;
}
