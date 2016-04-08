#include <stdio.h>
//#include <assert.h>
typedef long long LL;
const int maxt = 50000, maxn = 1000000, mod = 1000000007;
int f[maxn + 1], ans[maxn + 1], t, n;
LL g[maxn + 1], h[maxn + 1];
inline LL sqr(LL x) { return x * x; }
int main()
{
	f[1] = 1;
	for(int i = 1; i <= maxn; ++i)
	{
		for(int j = i + i; j <= maxn; j += i)
		{
			f[j] -= f[i];
			g[j] += i;
		}
		f[i] = i * f[i];
		g[i] = g[i - 1] + i + g[i];
	}
	for(int i = 1; i <= maxn; ++i)
		g[i] = sqr(g[i] % mod) % mod;
	for(int i = maxn; i; --i)
		g[i] -= g[i - 1];
	for(int i = 1; i <= maxn; ++i)
		for(int j = i, k = 1; j <= maxn; j += i, ++k)
			h[j] += f[i] * g[k] % mod;
	for(int i = 1; i <= maxn; ++i)
		h[i] += h[i - 1];
	for(int i = 1; i <= maxn; ++i)
	{
		ans[i] = (i * h[i] - h[i - 1]) % mod;
		if(ans[i] < 0)
			ans[i] += mod;
		h[i] = (h[i] + h[i - 1]) % mod;
	}
	scanf("%d", &t);
	//assert(1 <= t && t <= maxt);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		//assert(1 <= n && n <= maxn);
		printf("Case #%d: %d\n", Case, ans[n]);
	}
	return 0;
}
