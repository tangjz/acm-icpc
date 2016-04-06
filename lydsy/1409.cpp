#include <cstdio>
typedef long long LL;
const int maxn = 46341, maxs = 47;
int fib[maxs], tot, prime[maxn], mod, t, a, n, p;
bool vis[maxn];
struct Matrix
{
	int num1, num2;
	Matrix operator * (const Matrix &x) const
	{
		return (Matrix){(int)(((LL)num1 * x.num1 % mod + (LL)num2 * x.num2 % mod) % mod),
		(int)(((LL)num1 * x.num2 % mod + (LL)num2 * x.num1 % mod + (LL)num2 * x.num2 % mod) % mod)};
	}
	Matrix pow(int k)
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
int mod_fib(int x, int p)
{
	mod = p;
	return A.pow(x).num2;
}
int phi(int x)
{
	int ret = x;
	for(int i = 0; i < tot && prime[i] * prime[i] <= x; ++i)
		if(x % prime[i] == 0)
			for(ret -= ret / prime[i]; x % prime[i] == 0; x /= prime[i]);
	if(x > 1)
		ret -= ret / x;
	return ret;
}
int mod_pow(int x, LL k, int p)
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
	fib[1] = 1;
	for(int i = 2; i < maxs; ++i)
		fib[i] = fib[i - 1] + fib[i - 2];
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d%d", &t, &a);
	while(t--)
	{
		scanf("%d%d", &n, &p);
		if(n < maxs)
		{
			printf("%d\n", mod_pow(a, fib[n], p));
			continue;
		}
		int phip = phi(p);
		printf("%d\n", mod_pow(a, mod_fib(n, phip) + (LL)phip, p));
	}
	return 0;
}
