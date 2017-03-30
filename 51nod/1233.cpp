#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 1000003, mod = 1000000007;
int fact[maxn], iact[maxn], f[maxn];
inline int C(int x, int y)
{
	return x < y ? 0 : (LL)fact[x] * iact[y] % mod * iact[x - y] % mod;
}
inline int g(int n, int x)
{
	return (((LL)(n - x + n % x) * (n / x)) >> 1) % mod;
}
int solve(int n, int m, int p)
{
	int ret = 0;
	for(int i = 1; i <= n; ++i)
		ret = (ret + (LL)f[i] * g(n, i) % mod * g(m, i)) % mod;
	ret = ((ret << 1) + (LL)n * C(m, p) + (LL)m * C(n, p)) % mod;
	return ret;
}
int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	if(n > m)
		std::swap(n, m);
	iact[1] = 1;
	for(int i = 2; i <= m + 1; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	fact[0] = iact[0] = 1;
	for(int i = 1; i <= m + 1; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	for(int i = k - 1; i <= n + 1; ++i)
		f[i] = C(i - 1, k - 2);
	for(int i = k - 1; i <= n + 1; ++i)
		for(int j = i + i; j <= n + 1; j += i)
			if((f[j] -= f[i]) < 0)
				f[j] += mod;
	int ans = solve(n + 1, m + 1, k) - solve(n - 1, m - 1, k);
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
