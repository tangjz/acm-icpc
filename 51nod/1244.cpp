#include <map>
#include <cstdio>
using namespace std;
const int maxn = 4641589;
map<long long, long long> Hash;
int tot, prime[maxn], mu[maxn], f[maxn];
bool vis[maxn];
long long F(long long x)
{
	if(x < maxn)
		return f[x];
	if(Hash.count(x))
		return Hash[x];
	long long ret = 1;
	for(long long i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		ret -= F(x / i) * (j - i + 1);
	}
	return Hash[x] = ret;
}
int main()
{
	mu[1] = f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			mu[i] = -1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
				mu[i * prime[j]] = -mu[i];
		}
		f[i] = f[i - 1] + mu[i];
	}
	long long a, b;
	scanf("%lld%lld", &a, &b);
	printf("%lld\n", F(b) - F(a - 1));
	return 0;
}
