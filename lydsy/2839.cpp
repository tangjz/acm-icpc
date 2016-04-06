#include <cstdio>
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
int inv[maxn], n, k, ans;
int mod_inv(int x)
{
	return x <= 1 ? x : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
int main()
{
	scanf("%d%d", &n, &k);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	inv[0] = 1;
	for(int i = 1; i <= n; ++i)
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	for(int i = n, j = 2; i >= k; --i, j = (LL)j * j % mod)
		ans = (ans + ((i - k) & 1 ? -1LL : 1LL) * j * inv[n - i] % mod * inv[i - k]) % mod;
	ans = (LL)ans * mod_inv(inv[n]) % mod * inv[k] % mod;
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
