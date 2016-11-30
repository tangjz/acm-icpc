#include <cstdio>
const int maxn = 101;
int n;
long long c, p, t, a[maxn], b[maxn];
long long cnt(long long lim)
{
	long long ret = 0, tmp = 0, tot;
	for(int i = 1; i <= n && tmp < lim; ++i)
	{
		if(tmp + a[i] <= lim)
			b[i] = a[i];
		else
			b[i] = lim - tmp;
		tmp += b[i];
	}
	for(int i = n; i; --i)
	{
		if(!b[i])
			continue;
		tmp = (b[i] - 1) / c + 1;
		ret += tmp * i * p << 1;
		tot = tmp * c;
		for(int j = i; j && tot; --j)
			if(tot >= b[j])
			{
				tot -= b[j];
				b[j] = 0;
			}
			else
			{
				b[j] -= tot;
				tot = 0;
			}
	}
	return ret;
}
int main()
{
	long long L = 0, R = 0, M;
	scanf("%d%lld%lld%lld", &n, &c, &p, &t);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%lld", a + i);
		R += a[i];
	}
	while(L < R)
	{
		M = L + R + 1 >> 1;
		if(cnt(M) <= t)
			L = M;
		else
			R = M - 1;
	}
	printf("%lld\n", L);
	return 0;
}
