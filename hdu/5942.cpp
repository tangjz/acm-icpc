#include <cmath>
#include <stdio.h>
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
int sig[maxn], mu[maxn];
inline int Sig(LL n)
{
	if(n < maxn)
		return sig[(int)n];
	LL ret = 0;
	for(LL i = 1, j, k; i <= n; i = j)
	{
		k = n / i;
		j = n / k + 1;
		ret += k * (j - i);
	}
	return (int)(ret % mod);
}
int main()
{
	mu[1] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		++sig[i];
		for(int j = i + i; j < maxn; j += i)
		{
			++sig[j];
			mu[j] -= mu[i];
		}
		if((sig[i] += sig[i - 1]) >= mod)
			sig[i] -= mod;
	}
	int t;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		int ans = 0;
		LL n, tmp;
		scanf("%I64d", &n);
		for(int i = 1; (tmp = (LL)i * i) <= n; ++i)
			if(mu[i] > 0 && (ans += Sig(n / tmp)) >= mod)
				ans -= mod;
			else if(mu[i] < 0 && (ans -= Sig(n / tmp)) < 0)
				ans += mod;
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
