#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 10000001, maxp = 664580, mod = 1000000007;
int a, b, c, x[maxn + 1], p[maxn + 1];
int tot, prime[maxp], f[maxn], ans;
LL m;
void mod_inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%lld%d%d%d%d", &m, x + 1, &a, &b, &c);
	int beg, end;
	p[x[1]] = 1;
	for(int i = 2; i <= c + 1; ++i)
	{
		x[i] = ((LL)a * x[i - 1] + b) % c + 1;
		if(p[x[i]] || i > m)
		{
			beg = i <= m ? p[x[i]] : i;
			end = i;
			break;
		}
		p[x[i]] = i;
	}
	memset(p + 1, 0, c * sizeof(int));
	int *cnt = p;
	ans = 1;
	for(int i = 1; i < beg; ++i)
	{
		ans = (LL)ans * x[i] % mod;
		mod_inc(cnt[x[i]], 1);
	}
	if(beg < end)
	{
		int len = end - beg;
		if(m >= end - 1)
		{
			int tmp = 1, count = (m - beg + 1) / len % mod;
			for(int i = beg; i < end; ++i)
			{
				tmp = (LL)tmp * x[i] % mod;
				mod_inc(cnt[x[i]], count);
			}
			ans = (LL)ans * mod_pow(tmp, (m - beg + 1) / len % (mod - 1)) % mod;
		}
		int pos = beg + (m - beg + 1) % len;
		for(int i = beg; i < pos; ++i)
		{
			ans = (LL)ans * x[i] % mod;
			mod_inc(cnt[x[i]], 1);
		}
	}
	for(int i = 2; i <= c; ++i)
	{
		if(!f[i])
			prime[tot++] = f[i] = i;
		for(int j = 0, k = c / i; j < tot && prime[j] <= k; ++j)
		{
			f[i * prime[j]] = prime[j];
			if(i % prime[j] == 0)
				break;
		}
	}
	for(int i = c; i >= 2; --i)
	{
		if(i == f[i])
			continue;
		mod_inc(cnt[f[i]], cnt[i]);
		mod_inc(cnt[i / f[i]], cnt[i]);
	}
	for(int i = 0; i < tot; ++i)
		ans = (LL)ans * (cnt[prime[i]] + 1) % mod;
	printf("%d\n", ans);
	return 0;
}
