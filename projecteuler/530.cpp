#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 31622777;
int tot, prime[maxn >> 3], d[maxn], phi[maxn];
LL f(LL n)
{
	static LL his_n = -1, ret;
	if(his_n == n)
		return ret;
	his_n = n;
	ret = 0;
	for(LL i = 1, j, k; i <= n; i = j)
	{
		k = n / i;
		j = n / k + 1;
		ret += k * (j - i);
	}
	return ret;
}
int main()
{
	phi[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
		{
			phi[i] = i - 1;
			prime[tot++] = d[i] = i;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			int o = i * prime[j];
			d[o] = prime[j];
			if(d[i] == prime[j])
			{
				phi[o] = phi[i] * prime[j];
				break;
			}
			else
				phi[o] = phi[i] * (prime[j] - 1);
		}
	}
	for(LL n; scanf("%lld", &n) == 1; )
	{
		LL ans = 0, tmp;
		for(int i = 1; (tmp = (LL)i * i) <= n; ++i)
			ans += f(n / tmp) * phi[i];
		printf("%lld\n", ans);
	}
	return 0;
}
