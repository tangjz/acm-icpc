#include <cstdio>
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
int t, n, m, fact[maxn], iact[maxn], diff[maxn];
int main()
{
	diff[0] = iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		diff[i] = (LL)(diff[i - 2] + diff[i - 1]) * (i - 1) % mod;
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	}
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", n < m ? 0 : (int)((LL)fact[n] * iact[m] % mod * iact[n - m] % mod * diff[n - m] % mod));
	}
	return 0;
}
