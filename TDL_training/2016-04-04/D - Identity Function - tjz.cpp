#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 31623;
int tot, prime[maxn], lcm;
bool vis[maxn];
int mod_pow(int x, int k, int p)
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
int phi(int x, int flag = 0)
{
	int ret = x, lcm = 1;
	for(int i = 0; i < tot && prime[i] * prime[i] <= x; ++i)
		if(x % prime[i] == 0)
		{
			for(ret -= ret / prime[i]; x % prime[i] == 0; x /= prime[i]);
			lcm = lcm / __gcd(lcm, prime[i] - 1) * (prime[i] - 1);
		}
	if(x > 1)
	{
		ret -= ret / x;
		lcm = lcm / __gcd(lcm, x - 1) * (x - 1);
	}
	return flag ? lcm : ret;
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	int n;
	scanf("%d", &n);
	int tmp1 = phi(n);
	if(__gcd(n, tmp1) > 1)
	{
		puts("-1");
		return 0;
	}
	tmp1 = phi(n, -1);
	int tmp2 = phi(tmp1);
	int tmp3 = tmp2;
	for(int i = 0; i < tot && prime[i] * prime[i] <= tmp3; ++i)
		if(tmp3 % prime[i] == 0)
		{
			for( ; tmp2 % prime[i] == 0 && mod_pow(n, tmp2 / prime[i], tmp1) == 1; tmp2 /= prime[i]);
			for( ; tmp3 % prime[i] == 0; tmp3 /= prime[i]);
		}
	if(tmp3 > 1 && mod_pow(n, tmp2 / tmp3, tmp1) == 1)
		tmp2 /= tmp3;
	printf("%d\n", tmp2);
	return 0;
}
