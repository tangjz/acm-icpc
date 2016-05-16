#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxm = 50001, maxs = 1 << 16, mod = 1000000007;
int n, m, len, inv_len, tot, prime[maxm], vis[maxm], x[maxs];
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
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	for(int i = 2; i < maxm; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) < maxm; ++j)
		{
			vis[o] = 1;
			if(i % prime[j] == 0)
				break;
		}
		vis[i] ^= 1;
	}
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(len = 0; 1 << len <= m; ++len);
		inv_len = mod_pow(mod + 1 >> 1, len);
		len = 1 << len;
		memcpy(x, vis, (m + 1) * sizeof(int));
		memset(x + m + 1, 0, (len - m - 1) * sizeof(int));
		FWT(x, len, 0);
		for(int i = 0; i < len; ++i)
			x[i] = mod_pow(x[i], n);
		FWT(x, len, 1);
		printf("%d\n", x[0]);
	}
	return 0;
}
