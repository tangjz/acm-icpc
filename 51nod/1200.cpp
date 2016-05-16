#include <stdio.h>
typedef long long LL;
const int maxm = 50001, maxs = 1 << 16, mod = 1000000007;
int x[maxs], y[maxs], inv_len;
inline void FWT_iterate(int x[], int len, int delta)
{
	for(int i = 0; i < len; i += delta << 1)
		for(int j = 0; j < delta; ++j)
		{
			int t = x[i + delta + j];
			x[i + delta + j] = x[i + j] - t < 0 ? x[i + j] - t + mod : x[i + j] - t;
			x[i + j] = x[i + j] + t >= mod ? x[i + j] + t - mod : x[i + j] + t;
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
int n, m, len, tot, prime[maxm];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 2; i <= m; ++i)
	{
		if(!x[i])
			prime[tot++] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) <= m; ++j)
		{
			x[o] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	for(int i = 2; i <= m; ++i)
		x[i] = x[i] ^ 1;
	for(len = 0; 1 << len <= m; ++len);
	inv_len = mod_pow(mod + 1 >> 1, len);
	len = 1 << len;
	FWT(x, len, 0);
	for(int i = 0; i < len; ++i)
		x[i] = mod_pow(x[i], n);
	FWT(x, len, 1);
	printf("%d\n", x[0]);
	return 0;
}
