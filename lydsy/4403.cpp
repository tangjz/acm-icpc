#include <cstdio>
typedef long long LL;
const int mod = 1000003;
int fact[mod], inv[mod], t, n, l, r, ans;
int mod_fact(int n, int m)
{
	if(n < m)
		return 0;
	if(n >= mod)
		return (LL)mod_fact(n / mod, m / mod) * mod_fact(n % mod, m % mod) % mod;
	return (LL)fact[n] * inv[fact[m]] * inv[fact[n - m]] % mod;
}
int main()
{
	fact[0] = fact[1] = inv[1] = 1;
	for(int i = 2; i < mod; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &l, &r);
		ans = mod_fact(r - l + 1 + n, n) - 1;
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
