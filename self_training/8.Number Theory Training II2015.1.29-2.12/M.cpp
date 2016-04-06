#include <cmath>
#include <cstdio>
const int mod = 9937, maxx = 50000;
int tot, prime[maxx], pphi[maxx], n, m, sum, ans;
bool vis[maxx];
int pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = ret * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ret;
}
int phi(int x)
{
	if(x < maxx)
		return pphi[x] % mod;
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
	return ret % mod;
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
	while(scanf("%d%d", &n, &m) == 2)
	{
		sum = 0;
		for(int i = 1, j = (int)sqrt(n); i <= j; ++i)
			if(n % i == 0)
			{
				sum += phi(n / i) * pow(m, i) % mod;
				if(sum >= mod)
					sum -= mod;
				if(n / i != i)
				{
					sum += phi(i) * pow(m, n / i) % mod;
					if(sum >= mod)
						sum -= mod;
				}
			}
		for(ans = 0; ans < mod; ++ans)
			if((long long)ans * n % mod == sum % mod)
				break;
		printf("%d\n", ans);
	}
	return 0;
}
