#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, INF = ~0u >> 1;
int n, a[maxn], lim;
LL ans;
int solve(int m)
{
	if(a[0] <= (LL)m * n || a[0] % m)
		return 0;
	int k = a[0] / m - n;
	return (k - 1) / n + 1;
}
int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		std::sort(a, a + n);
		lim = 0;
		for(int i = 1; i < n; ++i)
			if(a[i - 1] != a[i])
				lim = std::__gcd(lim, a[i] - a[i - 1]);
		if(!lim)
			lim = a[0];
		else if(lim % n)
		{
			puts("0");
			continue;
		}
		else
			lim /= n;
		ans = 0;
		for(int i = 1; (LL)i * i <= lim; ++i)
		{
			if(lim % i)
				continue;
			ans += solve(i);
			if(i * i < lim)
				ans += solve(lim / i);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
