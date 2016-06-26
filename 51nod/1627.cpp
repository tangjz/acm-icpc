#include <cstdio>
typedef long long LL;
const int maxn = 200001, mod = 1000000007;
int n, m, fact[maxn], iact[maxn];
int main()
{
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	while(scanf("%d%d", &n, &m) == 2)
		printf("%d\n", (int)((LL)fact[n + m - 4] * iact[n - 2] % mod * iact[m - 2] % mod));
	return 0;
}
