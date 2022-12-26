#include <map>
#include <cstdio>
using namespace std;
map<int, int> f;
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
int phi(int x)
{
	int ret = x;
	for(int i = 2; i * i <= x; ++i)
		if(x % i == 0)
		{
			ret -= ret / i;
			while(x % i == 0)
				x /= i;
		}
	if(x > 1)
		ret -= ret / x;
	return ret;
}
int F(int x)
{
	if(f.count(x))
		return f[x];
	int p = phi(x);
	return f[x] = pow(2, F(p) + p, x);
}
int main()
{
	int t, n;
	scanf("%d", &t);
	f[1] = 0;
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", F(n));
	}
	return 0;
}
