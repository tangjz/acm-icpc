#include <cstdio>
const int maxn = 10000001;
int n, m, v, a[maxn], b, c, p;
long long ans;
int main()
{
	scanf("%d%d%d%d%d%d%d", &n, &m, &v, a, &b, &c, &p);
	for(int i = 1; i <= n; ++i)
		a[i] = (a[i - 1] * (long long)b + c) % p;
	for(int i = 1, j = 1, c = 0; i <= n; ++i)
	{
		for( ; j <= n && c < m; ++j)
			if(a[j] >= v)
				++c;
		if(c == m)
			ans += n - j + 2;
		if(a[i] >= v)
			--c;
	}
	printf("%lld\n", ans);
	return 0;
}
