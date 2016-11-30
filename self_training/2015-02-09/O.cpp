#include <cstdio>
int t, n, m;
int pow(int x, int k, int p)
{
	int ret = 1 % p;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % p;
		x = (long long)x * x % p;
		k >>= 1;
	}
	return ret;
}
int phi(int x)
{
	int ret = x, tmp = x;
	for(int i = 2; (long long)i * i <= tmp; ++i)
		if(tmp % i == 0)
		{
			ret -= ret / i;
			while(tmp % i == 0)
				tmp /= i;
		}
	if(tmp > 1)
		ret -= ret / tmp;
	return ret;
}
int check(int x, int k, int p)
{
	int ret = 1;
	while(k--)
	{
		ret *= x;
		if(ret > p)
			return ret;
	}
	return ret;
}
int f(int x, int p)
{
	if(!x)
		return 1 % p;
	int tmp = f(x / 10, phi(p));
	if(check(x % 10, tmp, p) >= p)
		return pow(x % 10, tmp, p) + p;
	else
		return check(x % 10, tmp, p);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", f(n, m) % m);
	}
	return 0;
}
