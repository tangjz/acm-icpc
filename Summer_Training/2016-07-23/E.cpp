#include <stdio.h>
typedef long long LL;
const int maxn = 20, maxm = 100000, maxs = 1 << maxn, mod = 1000000007;
int n, m, val[maxm], len, inv_len, x[maxs], sz[maxs];
char str[maxm + 1];
inline void FWT_iterate(int x[], int len, int delta)
{
	for(int i = 0, j, t, px = 0, py = delta; i < len; i += delta << 1, px = py, py += delta)
		for(j = 0; j < delta; ++j, ++px, ++py)
		{
			t = x[py];
			x[py] = x[px] - t < 0 ? x[px] - t + mod : x[px] - t;
			x[px] = x[px] + t >= mod ? x[px] + t - mod : x[px] + t;
		}
}
inline void FWT(int x[], int len, int flag)
{
	if(!flag)
		for(int i = 1; i < len; i <<= 1)
			FWT_iterate(x, len, i);
	else
	{
		for(int i = len >> 1; i > 0; i >>= 1)
			FWT_iterate(x, len, i);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * inv_len % mod;
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", str);
		for(int j = 0; j < m; ++j)
			if(str[j] == '1')
				val[j] |= 1 << i;
	}
	for(int i = 0; i < m; ++i)
		++x[val[i]];
	len = 1 << n;
	inv_len = 1;
	for(int i = 0; i < n; ++i)
		inv_len = (LL)inv_len * ((mod + 1) >> 1) % mod;
	for(int i = 1; i < len; ++i)
		sz[i] = sz[i >> 1] + (i & 1);
	for(int i = 0; i < len; ++i)
		if(sz[i] > n - sz[i])
			sz[i] = n - sz[i];
	FWT(x, len, 0);
	FWT(sz, len, 0);
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * sz[i] % mod;
	FWT(x, len, 1);
	int ans = n * m;
	for(int i = 0; i < len; ++i)
		if(ans > x[i])
			ans = x[i];
	printf("%d\n", ans);
	return 0;
}
