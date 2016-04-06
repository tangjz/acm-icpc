#include <cstdio>
typedef long long LL;
const int maxn = 44722, maxs = 10;
int tot, prime[maxn], n, m, b, mod, cnt, p[maxs], c[maxs], pp[maxs], ans;
bool vis[maxn + 1];
void exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
int mod_inv(int x, int p)
{
	int s, t;
	exgcd(x, p, s, t);
	return s < 0 ? s + p : s;
}
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
		k >>= 1;
	}
	return ret;
}
int C(int n, int m, int p, int c, int pp)
{
	int ret = 1, cnt = 0;
	for(int i = 1, o; i <= m; ++i)
	{
		for(o = n + 1 - i; o % p == 0; o /= p, ++cnt);
		ret = (LL)ret * o % pp;
		for(o = i; o % p == 0; o /= p, --cnt);
		ret = (LL)ret * mod_inv(o, pp) % pp;
	}
	if(cnt >= c)
		return 0;
	ret = (LL)ret * mod_pow(p, cnt, pp) % pp;
	return ret;
}
int calc(int n, int m, int mod)
{
	cnt = 0;
	for(int i = 0; i < tot && prime[i] * prime[i] <= mod; ++i)
		if(mod % prime[i] == 0)
		{
			for(c[cnt] = 0, pp[cnt] = 1; mod % prime[i] == 0; mod /= prime[i], ++c[cnt], pp[cnt] *= prime[i]);
			p[cnt++] = prime[i];
		}
	if(mod > 1)
	{
		p[cnt] = pp[cnt] = mod;
		c[cnt++] = 1;
		mod = 1;
	}
	if(m > n - m)
		m = n - m;
	int res = 0;
	for(int i = 0; i < cnt; ++i)
	{
		int x = mod_inv(mod, pp[i]);
		x = (LL)x * (C(n, m, p[i], c[i], pp[i]) - res) % pp[i];
		if(x < 0)
			x += pp[i];
		res += x * mod;
		mod *= pp[i];
	}
	return res;
}
int main()
{
	for(int i = 2; i <= maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, k = maxn / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d%d%d%d", &n, &m, &b, &mod);
	ans = calc(m + b - 1, m, mod);
	for(int i = 1, j = ans; i < n; ++i)
	{
		if(--j < 0)
			j += mod;
		ans = (LL)ans * j % mod;
	}
	printf("%d\n", ans);
	return 0;
}
