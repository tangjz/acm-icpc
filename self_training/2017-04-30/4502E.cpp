#include <cstdio>
typedef long long LL;
const int maxn = 1001, mod = 1000000007;
int n, fact[maxn], iact[maxn], inv2, inv3;
int main()
{
	scanf("%d", &n);
	iact[1] = 1;
	for(int i = 2; i <= n; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	inv2 = iact[2];
	inv3 = iact[3];
	fact[0] = iact[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	int ans = 0;
	for(int i = 0; i <= n - 1 - i; ++i)
	{
		if(i > 1) // && n - 1 - i > 1
		{ // one degree is 4
			int ways = (LL)fact[n] * inv2 % mod * inv2 % mod;
			if(i == n - 1 - i)
				ways = (LL)ways * inv2 % mod;
			(ans += ways) >= mod && (ans -= mod);
		}
		for(int j = i + !i; j <= n - 2 - i - j; ++j) // two degrees are 3
		{
			int ways = (LL)fact[n] * inv2 % mod;
			if(i == j && j == n - 2 - i - j)
				ways = (LL)ways * inv2 % mod * inv3 % mod;
			else if(i == j || j == n - 2 - i - j)
				ways = (LL)ways * inv2 % mod;
			(ans += ways) >= mod && (ans -= mod);
		}
	}
	printf("%d\n", ans);
	return 0;
}
