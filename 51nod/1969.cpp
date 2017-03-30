#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 30001, seed = 998244353, mod = 1000000007;
int sz[2], f[2][maxn], t, n, base, ans;
int main()
{
	for(int i = 0; i * (3 * i - 1) >> 1 < mod; ++i)
	{
		f[i & 1][sz[i & 1]++] = i * (3 * i - 1) >> 1;
		if(i * (3 * i + 1) >> 1 < mod)
			f[i & 1][sz[i & 1]++] = i * (3 * i + 1) >> 1;
	}
	std::sort(f[0], f[0] + sz[0]);
	std::sort(f[1], f[1] + sz[1]);
	scanf("%d%d", &t, &base);
	while(t--)
	{
		scanf("%d", &n);
		if(n == *std::lower_bound(f[0], f[0] + sz[0], n))
			n = 1;
		else if(n == *std::lower_bound(f[1], f[1] + sz[1], n))
			n = seed - 1;
		else
			n = 0;
		ans = ((LL)ans * base + n) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
