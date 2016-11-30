#include <cstdio>
const int p = 1000000007, maxn = 2001;
int n, x, inv[maxn];
long long d;
int C(long long n, int m)
{
	int ret = 1;
	for(int i = 0; i < m; ++i)
		ret = (n - i) % p * ret % p * inv[i + 1] % p;
	return ret;
}
int main()
{
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = (long long)(p - p / i) * inv[p % i] % p;
	while(scanf("%d%lld%d", &n, &d, &x) == 3 && n + d + x)
	{
		int ans = 0;
		for(int i = 0; i * x <= n; ++i)
		{
			int j = n - i * x, tmp = C(d, i);
			tmp = (long long)tmp * C(j + d - 1, j) % p;
			if(i & 1 && tmp)
				tmp = p - tmp;
			ans += tmp;
			if(ans >= p)
				ans -= p;
		}
		printf("%d\n", ans);
	}
	return 0;
}
