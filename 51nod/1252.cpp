#include <cstdio>
#include <cstring>
#include <cassert>
const int maxm = 101, maxp = 46341, maxs = 10;
typedef long long LL;
int t, n, m, q, p, lim, f[maxm][maxm * maxm], coeff[maxm * maxm], g[maxm * maxm], ans;
int tot, prime[maxp], cnt, fact[maxs], exp[maxs];
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
		for(int j = 0, k = (maxp - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &n, &m, &q, &p);
		if(n == m)
		{
			printf("%d\n", 1 % p);
			continue;
		}
		lim = n - m < m * q ? n - m : m * q;
		// coeff[i] = C(i, q)
		int tmp = p;
		cnt = 0;
		for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
			if(tmp % prime[i] == 0)
				for(fact[cnt++] = prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
		if(tmp > 1)
			fact[cnt++] = tmp;
		memset(exp, 0, cnt * sizeof(int));
		memset(coeff, 0, q * sizeof(int));
		coeff[q] = 1;
		for(int i = q + 1, o = 1; i < lim; ++i)
		{
			int fz = i, fm = i - q;
			for(int j = 0; j < cnt; ++j)
			{
				for( ; fz % fact[j] == 0; ++exp[j], fz /= fact[j]);
				for( ; fm % fact[j] == 0; --exp[j], fm /= fact[j]);
			}
			coeff[i] = o = (LL)o * fz % p * mod_inv(fm) % p;
			for(int j = 0; j < cnt; ++j)
				if(exp[j])
					coeff[i] = (LL)coeff[i] * mod_pow(fact[j], exp[j]) % p;
		}
		f[0][0] = 1;
		for(int i = 1; i <= m; ++i)
		{
			f[i][0] = 1;
			for(int j = 1; j <= lim; ++j)
			{
				f[i][j] = (LL)i * (f[i][j - 1] - (j > q ? (LL)coeff[j - 1] * f[i - 1][j - 1 - q] % p : 0)) % p;
				if(f[i][j] < 0)
					f[i][j] += p;
			}
		}
		g[lim] = mod_pow(n - m, n - m - lim);
		for(int i = lim - 1; i >= 0; --i)
			g[i] = (LL)g[i + 1] * (n - m) % p;
		// coeff[i] = C(n - m - 1, i)
		memset(exp, 0, cnt * sizeof(int));
		coeff[0] = 1;
		for(int i = 1, o = 1; i < lim; ++i)
		{
			int fz = n - m - i, fm = i;
			for(int j = 0; j < cnt; ++j)
			{
				for( ; fz % fact[j] == 0; ++exp[j], fz /= fact[j]);
				for( ; fm % fact[j] == 0; --exp[j], fm /= fact[j]);
			}
			coeff[i] = o = (LL)o * fz % p * mod_inv(fm) % p;
			for(int j = 0; j < cnt; ++j)
				if(exp[j])
					coeff[i] = (LL)coeff[i] * mod_pow(fact[j], exp[j]) % p;
		}
		ans = 0;
		for(int i = 1; i <= lim; ++i)
			ans = (ans + (LL)coeff[i - 1] * f[m][i] % p * g[i]) % p;
		// ans = (LL)ans * C(n, m) % p;
		memset(exp, 0, cnt * sizeof(int));
		for(int i = 1; i <= m; ++i)
		{
			int fz = n + 1 - i, fm = i;
			for(int j = 0; j < cnt; ++j)
			{
				for( ; fz % fact[j] == 0; ++exp[j], fz /= fact[j]);
				for( ; fm % fact[j] == 0; --exp[j], fm /= fact[j]);
			}
			ans = (LL)ans * fz % p * mod_inv(fm) % p;
		}
		for(int i = 0; i < cnt; ++i)
			if(exp[i])
				ans = (LL)ans * mod_pow(fact[i], exp[i]) % p;
		printf("%d\n", ans);
	}
	return 0;
}
