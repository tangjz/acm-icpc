#include <cmath>
#include <cstdio>
const long long maxr = 1e15;
int t, k;
long long n, a[12], now = 1, L, R, M, ret;
long long gcd(long long x, long long y)
{
	return y ? gcd(y, x % y) : x;
}
void dfs(int dep, int flag)
{
	if(dep == k)
	{
		if(flag & 1)
			ret += M / now * flag;
		else
			ret -= M / now * flag;
		return;
	}
	long long r = gcd(now, a[dep]);
	if(log10(now / r) + log10(a[dep]) <= 15)
	{
		now *= a[dep] / r;
		dfs(dep + 1, flag + 1);
		now /= a[dep] / r;
	}
	dfs(dep + 1, flag);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%lld", &k, &n);
		for(int i = 0; i < k; ++i)
			scanf("%lld", a + i); 
		L = 1, R = maxr;
		while(L < R)
		{
			M = L + R >> 1;
			ret = 0;
			dfs(0, 0);
			if(ret < n)
				L = M + 1;
			else
				R = M;
		}
		printf("%lld\n", L);
	}
	return 0;
}
