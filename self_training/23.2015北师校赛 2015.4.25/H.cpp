#include <cstdio>
const int mod = 1000000007;
int t;
long long n, m;
void inc(long long &x, long long y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
long long pow(long long x, unsigned long long k)
{
	long long ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % mod;
		x = (long long)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &n, &m);
		if(n == 1)
			puts("0");
		else if(n == 2)
			printf("%lld\n", m - 1);
		else
		{
			long long tmp = pow(m - 1, n);
			if(tmp && (n & 1))
				tmp = mod - tmp;
			inc(tmp, m - 1);
			tmp = tmp * pow(m, mod - 2) % mod;
			if(tmp && n & 1)
				tmp = mod - tmp;
			printf("%lld\n", tmp);
		}
	}
	return 0;
}
