#include <stdio.h>
const int maxn = 30001;
int f[maxn];
long long g[maxn];
int main()
{
	f[0] = 1;
	for(int i = 1; i < maxn; ++i)
		f[i] = f[i - 1] + i + 1;
	for(int i = 1; i < maxn; ++i)
		for(int j = 3, k = 1; j <= i; j += 3, ++k)
			g[i] += (long long)f[i - j] * k;
	for(int n; scanf("%d", &n) == 1; )
	{
		long long ans = 0;
		for(int i = 1; i <= n; ++i)
			ans += g[i];
		printf("%lld\n", ans);
	}
	return 0;
}
