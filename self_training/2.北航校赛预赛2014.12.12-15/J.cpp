#include <cstdio>
const int maxn = 100010, mod = 1000000007;
int t, n, f[maxn];
int main()
{
	for(int i = 2, fact = 1; i < maxn; ++i)
	{
		f[i] = ((long long)i * f[i - 1] + (i - 1ll) * fact) % mod;
		fact = fact * (long long)i % mod; 
	}
	while(scanf("%d", &n) == 1)
		printf("Case #%d: %d\n", ++t, f[n]);
	return 0;
}
