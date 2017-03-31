#include <stdio.h>
typedef long long LL;
const int maxn = 500001, maxd = 20, maxl = 1000001, mod = 1000000007;
int n, m, tot, prime[maxn], d[maxn], sig[maxn], inv[maxd], f[maxn], g[maxn];
char buf[maxl];
int main()
{
	scanf("%d%s", &n, buf);
	for(int i = 0; buf[i]; m = (10LL * m + buf[i++] - '0') % mod);
	d[1] = sig[1] = inv[1] = 1;
	for(int i = 2; i < maxd; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	for(int i = 2; i <= n; ++i)
	{
		if(!d[i])
		{
			prime[tot++] = d[i] = i;
			sig[i] = m;
		}
		for(int j = 0, k; (k = i * prime[j]) <= n; ++j)
		{
			d[k] = prime[j];
			if(d[i] == prime[j])
			{
				int u = i, c = 1;
				for( ; d[u] == prime[j]; u /= prime[j], ++c);
				if(u == 1)
					sig[k] = (LL)sig[i] * (m + c - 1) % mod * inv[c] % mod;
				else
					sig[k] = (LL)sig[u] * sig[k / u] % mod;
				break;
			}
			else
				sig[k] = (LL)sig[i] * m % mod;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", f + i);
		for(int j = i, k = 1; j <= n; j += i, ++k)
			g[j] = (g[j] + (LL)f[i] * sig[k]) % mod;
	}
	for(int i = 1; i <= n; ++i)
		printf("%d%c", g[i], " \n"[i == n]);
	return 0;
}
