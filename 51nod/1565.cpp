#include <stdio.h>
#include <cstring>
typedef unsigned UL;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 200001, maxs = ((maxn - 1) >> 6) + 2, INF = 0x3f3f3f3f;
const char *gene = "AGCT";
int n, m, k, cnt[1 << 16 | 1], pos[maxn], sz, ans;
ULL f[5][maxs], g[maxs];
char s[maxn], t[maxn];
inline int popcount(UL x)
{
	return cnt[x >> 16] + cnt[x & 65535];
}
inline int popcount(ULL x)
{
	return popcount((UL)(x >> 32)) + popcount((UL)x);
}
int main()
{
	for(int i = 1; i < 1 << 16; ++i)
		cnt[i] = cnt[i >> 1] + (i & 1);
	scanf("%d%d%d%s%s", &n, &m, &k, s, t);
	sz = ((n - 1) >> 6) + 1;
	for(int i = 0; i < 4; ++i)
		for(int j = 0, p = -INF; j < n; ++j)
		{
			(gene[i] == s[j]) && (p = j);
			(j - p <= k) && (f[i][j >> 6] |= 1ULL << (j & 63));
		}
	for(int i = 0; i < 4; ++i)
		for(int j = n - 1, p = INF; j >= 0; --j)
		{
			(gene[i] == s[j]) && (p = j);
			(p - j <= k) && (f[i][j >> 6] |= 1ULL << (j & 63));
		}
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < m; ++j)
			(gene[i] == t[j]) && (pos[j] = i);
	memcpy(g, f[pos[m - 1]], sz * sizeof(ULL));
	for( ; sz && !g[sz - 1]; --sz);
	for(int i = m - 2; i >= 0; --i)
	{
		// shift right 1
		for(int j = 0; j < sz; ++j)
			g[j] = (g[j] >> 1) | ((g[j + 1] & 1) << 63);
		(sz && !g[sz - 1]) && (--sz);
		ULL *F = f[pos[i]];
		for(int j = 0; j < sz; ++j)
			g[j] &= F[j];
		for( ; sz && !g[sz - 1]; --sz);
	}
	for(int i = 0; i < sz; ++i)
		ans += popcount(g[i]);
	printf("%d\n", ans);
	return 0;
}
