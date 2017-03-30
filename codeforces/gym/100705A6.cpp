#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 1234569, mod = 1000000007;
int n, tot, pr[maxn >> 3 | 1], d[maxn], pk[maxn], ot[maxn], f[maxn], ans;
inline int lcm(int x, int y)
{
	return x / std::__gcd(x, y) * y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = pk[i] = i;
			ot[i] = 1;
		}
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
			{
				pk[k] = pk[i] * pr[j];
				ot[k] = ot[i];
				break;
			}
			else
			{
				pk[k] = pr[j];
				ot[k] = i;
			}
		}
	}
	for(int i = 2; i <= n; i <<= 1)
		f[i] = i >> (1 + (i > 4));
	for(int i = 1; i < tot; ++i)
		for(int j = 1, k = pr[i], lim = n / pr[i]; j <= lim; j = k, k *= pr[i])
			f[k] = k - j;
	for(int i = 2; i <= n; ++i)
	{
		if(ot[i] > 1)
			f[i] = lcm(f[pk[i]], f[ot[i]]);
		ans = (ans + (LL)f[i] * f[i]) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
