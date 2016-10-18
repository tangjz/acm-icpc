#include <stdio.h>
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
int n, m, s[maxn], fact[maxn], iact[maxn], pw[maxn], ans;
char str[maxn];
inline int C(int n, int m)
{
	return (LL)fact[n] * iact[m] % mod * iact[n - m] % mod;
}
int main()
{
	scanf("%d%d%s", &n, &m, str);
	for(int i = 0; str[i]; ++i)
		s[i] = (i ? s[i - 1] : 0) + (str[i] -= '0');
	iact[1] = 1;
	for(int i = 2; i <= n; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	fact[0] = iact[0] = pw[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
		pw[i] = 10LL * pw[i - 1] % mod;
	}
	if(m)
		for(int i = 0; i < n - m; ++i)
			ans = (ans + (LL)pw[i] * C(n - i - 2, m - 1) % mod * s[n - i - 2]) % mod;
	for(int i = m; i < n; ++i)
		ans = (ans + (LL)str[i] * pw[n - i - 1] % mod * C(i, m)) % mod;
	printf("%d\n", ans);
	return 0;
}
