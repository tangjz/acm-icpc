#include <stdio.h>
typedef long long LL;
const int maxn = 100001, maxm = 1000001, mod = 1000000007;
int fact[maxm << 1], iact[maxm];
int n, deg[maxn], ans;
int main()
{
	fact[0] = 1;
	for(int i = 1; i < maxm << 1; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	iact[1] = 1;
	for(int i = 2; i < maxm; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	iact[0] = 1;
	for(int i = 1; i < maxm; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	scanf("%d", &n);
	ans = 1;
	for(int i = 1; i < n; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		deg[u] += w;
		deg[v] += w;
		ans = (LL)ans * fact[w << 1] % mod * iact[w] % mod * iact[w] % mod * w % mod;
	}
	for(int i = 1; i <= n; ++i)
		ans = (LL)ans * fact[deg[i] - (i > 1)] % mod;
	printf("%d\n", ans);
	return 0;
}
