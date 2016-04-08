#include <cstdio>
const int mod = 10007;
int fact[mod], inv[mod];
int C(int n, int m)
{
	if(n < m)
		return 0;
	if(n >= mod)
		return C(n / mod, m / mod) * C(n % mod, m % mod) % mod;
	return (long long)fact[n] * inv[fact[m]] * inv[fact[n - m]] % mod;
}
int main()
{
	int t, n, m;
	fact[0] = 1;
	for(int i = 1; i < mod; ++i)
		fact[i] = fact[i - 1] * i % mod;
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = mod - mod / i * inv[mod % i] % mod;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", C(n, m));
	}
	return 0;
}
