#include <stdio.h>
typedef long long LL;
const int maxn = 14, maxp = 31623;
int p;
struct Matrix
{
	int num1, num2;
	Matrix operator * (const Matrix &x) const
	{
		return (Matrix){((LL)num1 * x.num1 + (LL)num2 * x.num2) % p,
		((LL)num1 * x.num2 + (LL)num2 * (x.num1 + (x.num2 << 1))) % p};
	}
	Matrix pow(LL k)
	{
		Matrix ret = (Matrix){1, 0}, tmp = *this;
		while(k)
		{
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A = {0, 1};
int f[maxn], g[maxn], tot, prime[maxp], t, n, y, x, s;
bool vis[maxp];
int mod_pow(int x, int k, int p)
{
	int ret = 1 % p;
	for(x %= p; k > 0; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
int phi(int x)
{
	int ret = x;
	for(int i = 0; i < tot && prime[i] * prime[i] <= x; ++i)
		if(x % prime[i] == 0)
		{
			ret -= ret / prime[i];
			for(x /= prime[i]; x % prime[i] == 0; x /= prime[i]);
		}
	if(x > 1)
		ret -= ret / x;
	return ret;
}
int main()
{
	f[1] = g[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		f[i] = f[i - 2] + (f[i - 1] << 1);
		g[i] = g[i - 1] + f[i] * f[i];
	}
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
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &n, &y, &x, &s);
		++s;
		int tmp = phi(s), val;
		if((LL)n * y < maxn)
			val = g[n * y];
		else
		{
			p = tmp << 1;
			Matrix tmp2 = A.pow((LL)n * y + 1);
			val = ((LL)tmp2.num1 * tmp2.num2 % p) >> 1;
			val += tmp;
		}
		val = mod_pow(x, val, s);
		printf("%d\n", val);
	}
	return 0;
}
