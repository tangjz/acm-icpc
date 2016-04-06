#include <stdio.h>
typedef long long LL;
const int mod = 1000000007, mod_len = mod + 1 << 1;
void mod_inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
struct Matrix
{
	int num1, num2;
	bool operator == (const Matrix &x) const
	{
		return num1 == x.num1 && num2 == x.num2;
	}
	Matrix operator * (const Matrix &x) const
	{
		return (Matrix){(int)(((LL)num1 * x.num1 + (LL)num2 * x.num2) % mod),
		(int)(((LL)num1 * x.num2 + (LL)num2 * (x.num1 + x.num2)) % mod)};
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
int fib(LL n)
{
	return A.pow(n % mod_len).num2;
}
int sum_fib(LL n)
{
	if(n <= 0)
		return 0;
	int ret = fib(n + 2) - 1;
	return ret < 0 ? ret + mod : ret;
}
int diff_fib(LL n)
{
	if(n <= 0)
		return 0;
	int ret = (n & 1 ? -fib(n - 1) : fib(n - 1)) - 1;
	return ret < 0 ? ret + mod : ret;
}
LL count_fib(LL n, LL m)
{
	if(n <= m)
		return 0;
	if(n <= (m << 1))
	{
		if(n == (m << 1))
			--n;
		return n - m >> 1;
	}
	if(n <= (m << 1) + m)
	{
		if(n == (m << 1) + m)
			--n;
		return (m - 1 >> 1) + (n - (m << 1));
	}
	if(n == (m << 2))
		--n;
	return (m - 1 >> 1) + (m - 1) + (n - (m << 1) - m + 1 >> 1);
}
int calc(LL n, LL m)
{
	if(n <= m)
	{
		if(n == m)
			--n;
		return sum_fib(n);
	}
	int ret = diff_fib(m - 1) - diff_fib((m << 1) - n - 1);
	if(ret < 0)
		ret += mod;
	if((~m & 1) && ret)
		ret = mod - ret;
	mod_inc(ret, sum_fib(m - 1));
	return ret;
}
int main()
{
	int t;
	LL n, m, k;
	scanf("%d", &t);
	while(t--)
	{
		int ans = 0;
		scanf("%lld%lld", &n, &m);
		if(m <= 2)
		{
			puts("0");
			continue;
		}
		if(m & 1)
		{
			k = n % (m << 2);
			int coeff = ((n / (m << 2) % mod) * ((m - 1 << 1) % mod) + count_fib(k, m)) % mod;
			mod_inc(ans, (LL)coeff * fib(m) % mod);
			if(k <= (m << 1))
				mod_inc(ans, calc(k, m));
			else
			{
				mod_inc(ans, calc(m << 1, m));
				int tmp = -calc(k - (m << 1), m);
				if(tmp < 0)
					tmp += mod;
				mod_inc(ans, tmp);
			}
		}
		else
		{
			k = n % (m << 1);
			int coeff = ((n / (m << 1) % mod) * ((m + 2 >> 1) % mod) + count_fib(k, m)) % mod;
			mod_inc(ans, (LL)coeff * fib(m) % mod);
			mod_inc(ans, calc(k, m));
		}
		printf("%d\n", ans);
	}
	return 0;
}
