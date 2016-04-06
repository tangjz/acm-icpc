#include <cstdio>
typedef long long LL;
const int maxn = 801, maxp = 32000, maxs = 10;
int n, m, p, c[maxn][maxn], ans;
int tot, prime[maxp], cnt, fact[maxs], exp[maxs], coeff;
bool vis[maxp];
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
int mod_inv(int x)
{
	int s, t;
	exgcd(x, p, s, t);
	return s < 0 ? s + p : s;
}
int mod_pow(int x, int k)
{
	int ret = 1 % p;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
		k >>= 1;
	}
	return ret;
}
int main()
{
	for(int i = 2; i < maxp; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) < maxp; ++j)
		{
			vis[o] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d%d%d", &n, &m, &p);
	for(int i = 0; i <= n; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
		{
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			if(c[i][j] >= p)
				c[i][j] -= p;
		}
	}
	int tmp = p;
	cnt = 0;
	for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
		if(tmp % prime[i] == 0)
			for(fact[cnt++] = prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
	if(tmp > 1)
		fact[cnt++] = tmp;
	coeff = 1;
	for(int i = 1; i <= n + 1; ++i)
	{
		int fz = m + i, fm = i;
		for(int j = 0; j < cnt; ++j)
		{
			for( ; fz % fact[j] == 0; ++exp[j], fz /= fact[j]);
			for( ; fm % fact[j] == 0; --exp[j], fm /= fact[j]);
		}
		coeff = (LL)coeff * fz % p * mod_inv(fm) % p;
	}
	for(int i = 0; i <= n; ++i)
	{
		int val = (LL)c[n][i] * coeff % p;
		for(int j = 0; j < cnt; ++j)
			if(exp[j])
				val = (LL)val * mod_pow(fact[j], exp[j]) % p;
		ans += val;
		if(ans >= p)
			ans -= p;
		if(i == m)
			break;
		int fz = m - i, fm = n + 1 + m - i;
		for(int j = 0; j < cnt; ++j)
		{
			for( ; fz % fact[j] == 0; ++exp[j], fz /= fact[j]);
			for( ; fm % fact[j] == 0; --exp[j], fm /= fact[j]);
		}
		coeff = (LL)coeff * fz % p * mod_inv(fm) % p;
	}
	printf("%d\n", ans);
	return 0;
}
