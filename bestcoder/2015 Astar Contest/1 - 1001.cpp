#include <cstdio>
const int maxn = 1000001, mod = 1000000007;
int t, n, f[maxn];
int main()
{
	f[0] = f[1] = 1;
	for(int i = 2; i < maxn; ++i)
		f[i] = (f[i - 1] + (i - 1LL) * f[i - 2]) % mod;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i)
	{
		scanf("%d", &n);
		printf("Case #%d:\n%d\n", i, f[n]);
	}
	return 0;
}
