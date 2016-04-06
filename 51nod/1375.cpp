#include <stdio.h>
typedef long long LL;
const int maxn = 100001, maxm = 1000001, mod = 998244353;
int n, k, m, a[maxm], fact[maxn], inv[maxn], pw2[maxn];
int main()
{
	scanf("%d%d", &n, &k);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	fact[0] = inv[0] = pw2[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
		pw2[i] = pw2[i - 1] << 1;
		if(pw2[i] >= mod)
			pw2[i] -= mod;
	}
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		++a[x];
		if(m < x)
			m = x;
	}
	for(int i = 1; i <= m; ++i)
		for(int j = i + i; j <= m; j += i)
			a[i] += a[j];
	for(int i = m; i; --i)
	{
		a[i] = k == -1 ? pw2[a[i]] - 1 : (k <= a[i] ? (LL)fact[a[i]] * inv[k] % mod * inv[a[i] - k] % mod: 0);
		for(int j = i + i; j <= m; j += i)
		{
			a[i] -= a[j];
			if(a[i] < 0)
				a[i] += mod;
		}
	}
	printf("%d\n", a[1]);
	return 0;
}
