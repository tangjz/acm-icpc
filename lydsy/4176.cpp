#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
map<int, int> Hash;
int tot, prime[maxn], f[maxn], n, ans;
bool vis[maxn];
inline void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
inline void dec(int &x, int y)
{
	x -= y;
	if(x < 0)
		x += mod;
}
int calc_mu(int x)
{
	if(x < maxn)
		return f[x];
	if(Hash.count(x))
		return Hash[x];
	LL ret = 1;
	for(int i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		ret -= (LL)calc_mu(x / i) * (j - i + 1);
	}
	ret %= mod;
	if(ret < 0)
		ret += mod;
	return Hash[x] = ret;
}
inline int calc_mu(int L, int R)
{
	int ret = calc_mu(R);
	dec(ret, calc_mu(L - 1));
	return ret;
}
inline int calc_sum(int x)
{
	LL ret = 0;
	for(int i = 1, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		ret += (LL)(x / i) * (j - i + 1);
	}
	ret %= mod;
	return ret * ret % mod;
}
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			f[i] = mod - 1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				f[i * prime[j]] = 0;
				break;
			}
			else
				dec(f[i * prime[j]], f[i]);
		}
		inc(f[i], f[i - 1]);
	}
	scanf("%d", &n);
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		inc(ans, (LL)calc_mu(i, j) * calc_sum(n / i) % mod);
	}
	printf("%d\n", ans);
	return 0;
}
