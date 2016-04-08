#include <cmath>
#include <cstdio>
int a, p;
bool isprime(int x)
{
	for(int i = 2, j = (int)sqrt(x); i <= j; ++i)
		if(x % i == 0)
			return 0;
	return 1;
}
int pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % p;
		x = (long long)x * x % p;
		k >>= 1;
	}
	return ret;
}
int main()
{
	while(scanf("%d%d", &p, &a) == 2 && p && a)
		puts(!isprime(p) && a == pow(a, p, p) ? "yes" : "no");
	return 0;
}