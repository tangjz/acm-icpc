#include <cstdio>
typedef long long LL;
const int mod = 10007;
int n, fact[mod], inv[mod];
int C(int x, int y)
{
	if(x < y)
		return 0;
	if(x < mod)
		return (LL)fact[x] * inv[y] * inv[x - y] % mod;
	return C(x / mod, y / mod) * C(x % mod, y % mod) % mod;
}
int main()
{
	scanf("%d", &n);
	fact[0] = 1;
	for(int i = 1; i < mod; ++i)
		fact[i] = fact[i - 1] * i % mod;
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;
	inv[0] = 1;
	for(int i = 1; i < mod; ++i)
		inv[i] = inv[i - 1] * inv[i] % mod;
	int ans = C(2 * n, n) - C(2 * n, n - 1);
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
