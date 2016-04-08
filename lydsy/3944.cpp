#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1664511;
map<LL, LL> Hash;
int tot, prime[maxn], f[maxn];
bool vis[maxn];
LL F(LL x)
{
	if(x < maxn)
		return f[x];
	if(Hash.count(x))
		return Hash[x];
	LL ret = 1;
	for(LL i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		ret -= F(x / i) * (j - i + 1);
	}
	return Hash[x] = ret;
}
LL calc(LL L, LL R)
{
	return F(R) - F(L - 1);
}
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			f[i] = -1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
			else
				f[i * prime[j]] = -f[i];
		}
		f[i] += f[i - 1];
	}
	int t;
	LL n;
	scanf("%d", &t);
	while(t--)
	{
		LL ans = 0;
		scanf("%lld", &n);
		for(LL i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			ans += (n / i) * (n / i + 1) / 2 * calc(i, j);
		}
		printf("%lld %lld\n", ans, F(n));
	}
	return 0;
}
