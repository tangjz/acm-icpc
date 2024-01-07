#include <stdio.h>
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
int t, n, m, k, fact[maxn], iact[maxn];
int main()
{
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &m, &k);
		if(m == 1)
		{
			printf("%d\n", n);
			continue;
		}
		if(m - 1 > n - m * k - 1)
		{
			puts("0");
			continue;
		}
		int ans = (LL)n % mod * fact[n - m * k - 1] % mod * iact[m] % mod * iact[n - m * k - m] % mod;
		printf("%d\n", ans);
	}
	return 0;
}
