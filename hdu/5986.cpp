#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = (int)1.9e6, maxd = 16;
int MOD;
struct Matrix
{
	int num1, num2;
	Matrix operator * (const Matrix &x) const
	{
		return (Matrix){((LL)num1 * x.num1 + (LL)num2 * x.num2) % MOD,
		((LL)num1 * x.num2 + (LL)num2 * (x.num1 + x.num2)) % MOD};
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
int mod_fib(int k, int p)
{
	MOD = p;
	return A.pow(k).num2;
}
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
int mod_pr_len(int p, int k)
{
	int ret = 1;
	if(p == 2)
		ret = 3;
	else if(p == 3)
		ret = 8;
	else if(p == 5)
		ret = 20;
	else if(mod_pow(5, (p - 1) >> 1, p) == 1)
		ret = p - 1;
	else
		ret = (p + 1) << 1;
	for(int i = 1; i < k; ++i)
		ret *= p;
	return ret;
}
int lcm(int x, int y)
{
	return x / __gcd(x, y) * y;
}
int tot, prime[maxn], d[maxn];
int mod_len(int n)
{
	int ret = 1;
	while(n > 1)
	{
		int pr = d[n], ex = 1;
		for(n /= pr; d[n] == pr; n /= pr, ++ex);
		ret = lcm(ret, mod_pr_len(pr, ex));
	}
	return ret;
}
int solve(int x, int n)
{
	int len, xx = x % n;
	static int cir[maxd];
	cir[0] = n;
	for(len = 1; ; ++len)
	{
		cir[len] = mod_len(cir[len - 1]);
		if(cir[len] == cir[len - 1])
			break;
		int yy = x % cir[len];
		for(int i = 1; i <= len; ++i)
			yy = mod_fib(yy, cir[len - i]);
		if(xx == yy)
			return len;
	}
	int M = cir[--len];
	static int systim, tim[maxn];
	++systim;
	for(int i = 1, yy = x % M; ; ++i)
	{
		yy = mod_fib(yy, M);
		if(tim[yy] == systim)
			break;
		tim[yy] = systim;
		int zz = yy;
		for(int j = 1; j <= len; ++j)
			zz = mod_fib(zz, cir[len - j]);
		if(xx == zz)
			return len + i;
	}
	return -1;
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
			prime[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * prime[j]) < maxn; ++j)
		{
			d[k] = prime[j];
			if(d[i] == prime[j])
				break;
		}
	}
	int t, x, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &x, &n);
		printf("%d\n", solve(x, n));
	}
	return 0;
}
