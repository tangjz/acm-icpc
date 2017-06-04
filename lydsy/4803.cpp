#include <cmath>
#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 10000001, maxp = 664579, maxs = 1000001;
int tot, pr[maxp], d[maxn], t, sz, cnt;
LL n, pp[maxp], ans[maxs];
bool isprime(LL x)
{
	if(x < maxn)
		return x == d[x];
	for(int i = 0, lim = (int)ceil(sqrt(x)); pr[i] <= lim; ++i)
		if(x % pr[i] == 0)
			return 0;
	return 1;
}
void dfs(int dep, LL val, LL phi)
{
	if(phi & 1 || dep == cnt)
	{
		if(phi == 1)
			ans[sz++] = val;
		return;
	}
	for(int i = dep; pp[i] <= phi + 1; ++i)
		if(phi % (pp[i] - 1) == 0)
		{
			LL nv = val * pp[i], np = phi / (pp[i] - 1);
			dfs(i + 1, nv, np);
			while(np % pp[i] == 0)
				dfs(i + 1, nv *= pp[i], np /= pp[i]);
		}
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pr[tot] = ~0u >> 1;
	// scanf("%d", &t);
	// while(t--)
	{
		scanf("%lld%d", &n, &t);
		if(n & 1) // phi(x) is even when x > 2
		{
			sz = 0;
			if(n == 1)
			{
				ans[sz++] = 1;
				ans[sz++] = 2;
			}
			for(int i = 0, o = 0; i < t && i < sz; ++i)
			{
				o ? putchar(' ') : o = 1;
				printf("%lld", ans[i]);
			}
			putchar('\n');
			return 0; // continue;
		}
		cnt = 0;
		for(int i = 0; i < tot; ++i)
			if(n % (pr[i] - 1) == 0)
				pp[cnt++] = pr[i];
		for(int i = n / maxn; i >= 1; --i)
			if(n % i == 0 && isprime(n / i + 1))
				pp[cnt++] = n / i + 1;
		pp[cnt] = n + 2;
		sz = 0;
		dfs(0, 1, n);
		std::sort(ans, ans + sz);
		// printf("%d\n", sz);
		for(int i = 0, o = 0; i < t && i < sz; ++i)
		{
			o ? putchar(' ') : o = 1;
			printf("%lld", ans[i]);
		}
		putchar('\n');
	}
	return 0;
}
