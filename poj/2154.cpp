#include <cmath>
#include <cstdio>
const int maxx = 50000;
int tot, prime[maxx], pphi[maxx], t, n, p, ans;
bool vis[maxx];
int pow(int x, int k)
{
	int ret = 1 % p;
	while(k)
	{
		if(k & 1)
			ret = ret * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ret;
}
int phi(int x)
{
	if(x < maxx)
		return pphi[x] % p;
	int ret = x;
	for(int i = 0; i < tot && (long long)prime[i] * prime[i] <= x; ++i)
		if(x % prime[i] == 0)
		{
			ret -= ret / prime[i];
			while(x % prime[i] == 0)
				x /= prime[i];
		}
	if(x > 1)
		ret -= ret / x;
	return ret % p;
}
int main()
{
	pphi[1] = 1;
	for(int i = 2; i < maxx; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			pphi[i] = i - 1;
		}
		for(int j = 0; j < tot && (long long)i * prime[j] < maxx; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				pphi[i * prime[j]] = pphi[i] * prime[j];
				break;
			}
			pphi[i * prime[j]] = pphi[i] * (prime[j] - 1);
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &p);
		ans = 0;
		for(int i = 1, j = (int)sqrt(n); i <= j; ++i)
			if(n % i == 0)
			{
				ans += phi(n / i) * pow(n % p, i - 1) % p;
				if(n / i != i)
					ans += phi(i) * pow(n % p, n / i - 1) % p;
				while(ans >= p)
					ans -= p;
			}
		printf("%d\n", ans);
	}
	return 0;
}