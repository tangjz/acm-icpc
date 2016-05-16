#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 100000;
int t, n, m, p, x, f[maxn + 1], c[maxn + 1];
bool vis[maxn + 1];
inline void mod_inc(int &x, int y)
{
	if((x += y) >= p)
		x -= p;
}
inline void mod_dec(int &x, int y)
{
	if((x -= y) < 0)
		x += p;
}
int mod_inv(int x)
{
	return x <= 1 ? x : p - p / x * (LL)mod_inv(p % x) % p;
}
int mod_pow(int x, int k)
{
	int ret = 1;
	for(k = (k %= p - 1) < 0 ? k + p - 1 : k; k; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &n, &m, &p, &x);
		memset(vis + 1, 0, m * sizeof(bool));
		memset(c + 1, 0, m * sizeof(int));
		for(register int xx; n--; )
		{
			scanf("%d", &xx);
			vis[xx] = 1;
		}
		for(register int i = 1; i <= m; ++i)
			f[i] = ((LL)f[i - 1] * x + 1) % p;
		register int ans = 1;
		for(register int i = m; i > 0; --i)
		{
			for(register int j = i + i; j <= m && !vis[i]; j += i)
				vis[i] |= vis[j];
			if(!vis[i])
				continue;
			c[i] = 1;
			for(int j = i + i; j <= m; j += i)
				c[i] -= c[j];
			ans = (LL)ans * mod_pow(f[i], c[i]) % p;
		}
		printf("%d\n", ans);
	}
	return 0;
}
