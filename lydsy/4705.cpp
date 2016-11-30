#include <stdio.h>
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
int fact[maxn << 1], iact[maxn];
int n, m, r, c, ans;
LL s;
inline int C(int n, int m)
{
	return (LL)fact[n] * iact[m] % mod * iact[n - m] % mod;
}
int main()
{
	fact[0] = 1;
	for(int i = 1; i < maxn << 1; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	scanf("%d%d%d%d%lld", &n, &m, &r, &c, &s);
	for(int i = r & 1; i <= r && i <= n; i += 2)
		if((i << 1) != n)
		{
			if((s - (LL)i * m) % (n - (i << 1)))
				continue;
			int j = (s - (LL)i * m) / (n - (i << 1));
			if(j >= 0 && j <= c && j <= m && (j & 1) == (c & 1))
				ans = (ans + (LL)C(n, i) * C(m, j) % mod * C((r - i >> 1) + n - 1, n - 1) % mod * C((c - j >> 1) + m - 1, m - 1)) % mod;
		}
		else if((LL)n * m == (s << 1))
			ans = (ans + (LL)C(n, i) * C((r - i >> 1) + n - 1, n - 1) % mod * C(c + m - 1, m - 1)) % mod;
	printf("%d\n", ans);
	return 0;
}
