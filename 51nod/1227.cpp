#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1000010, mod = 1000000007, inv2 = (mod + 1) >> 1, inv6 = (mod + 1) / 6;
map<LL, int> Hash;
int tot, prime[maxn], f[maxn], ans;
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
inline int num1(int L, int R)
{
	return ((L + R) * (R - L + 1LL) >> 1) % mod;
}
int calc_iphi(int x)
{
	if(x < maxn)
		return f[x];
	if(Hash.count(x))
		return Hash[x];
	int ret = x * (x + 1LL) % mod * ((x << 1) + 1) % mod * inv6 % mod;
	for(int i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		dec(ret, (LL)calc_iphi(x / i) * num1(i, j) % mod);
	}
	return Hash[x] = ret;
}
int calc(int n)
{
	int ret = n;
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		inc(ret, (j - i + 1LL) * calc_iphi(n / i) % mod);
	}
	return ret;
}
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = i - 1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
			if(i % prime[j] == 0)
			{
				f[i * prime[j]] = f[i] * prime[j];
				break;
			}
			else
				f[i * prime[j]] = f[i] * (prime[j] - 1);
		f[i] = (f[i - 1] + (LL)i * f[i]) % mod;
	}
	int a, b;
	scanf("%d%d", &a, &b);
	ans = calc(b);
	dec(ans, calc(a - 1));
	ans = (LL)ans * inv2 % mod;
	printf("%d\n", ans);
	return 0;
}
