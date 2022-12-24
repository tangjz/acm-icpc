#include <stdio.h>
//#include <cstring>
//#include <cassert>
const int maxd = 21, maxn = 1 << maxd;
int n, m, all, f[maxn], g[maxn], h[maxn];
char sz[maxn], r[maxn >> 1 | 1], b[maxn >> 1 | 1];
unsigned long long ans;
int main()
{
	register int i, j;
	/*assert(*/scanf("%d%d%s%s", &n, &m, r + 1, b + 1)/* == 4
	&& 1 <= n && n < maxn && 1 <= m && m < maxn
	&& strlen(r + 1) == n && strlen(b + 1) == m)*/;
	r[0] = b[0] = '1';
	for(all = 1; all <= n + m; all <<= 1);
	for(i = 1; i < all; ++i)
		sz[i] = sz[i >> 1] + (i & 1);
	for(i = 0; i <= n; ++i)
	{
		//assert(r[i] >= '1' && r[i] <= '9');
		f[i] |= (r[i] & 1) << sz[i];
	}
	for(i = 0; i <= m; ++i)
	{
		//assert(b[i] >= '1' && b[i] <= '9');
		g[i] |= (b[i] & 1) << sz[i];
	}
	for(i = 1; i < all; i <<= 1)
		for(j = 0; j < all; ++j)
			(j & i) && (f[j] ^= f[j ^ i], g[j] ^= g[j ^ i]);
	for(i = 0; i < all; ++i)
		(f[i] & 1) && (h[i] ^= g[i]);
	for(i = 1; i < all; i <<= 1)
		for(j = 0; j < all; ++j)
		{
			f[j] >>= 1;
			g[j] <<= 1;
			(f[j] & 1) && (h[j] ^= g[j]);
		}
	for(i = 1; i < all; i <<= 1)
		for(j = 0; j < all; ++j)
			(j & i) && (h[j] ^= h[j ^ i]);
	for(i = 1; i <= n + m; ++i)
		if((h[i] >> sz[i]) & 1)
			ans += (unsigned long long)i * i;
	printf("%llu\n", ans);
	return 0;
}
