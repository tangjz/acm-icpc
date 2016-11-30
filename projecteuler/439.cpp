#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 23333333, mod = 1000000000;
map<LL, int> Hash;
int tot, prime[maxn], d[maxn], f[maxn];
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
inline int num1(LL x)
{
	return x & 1 ? x % mod * ((x + 1 >> 1) % mod) % mod : (x >> 1) % mod * ((x + 1) % mod) % mod;
}
inline int num1(LL L, LL R)
{
	int ret = num1(R);
	dec(ret, num1(L - 1));
	return ret;
}
int calc_imu(LL x)
{
	if(x < maxn)
		return f[(int)x];
	if(Hash.count(x))
		return Hash[x];
	int ret = 1;
	for(LL i = 2, j, k; i <= x; i = j + 1)
	{
		k = x / i;
		j = x / k;
		dec(ret, (LL)num1(i, j) * calc_imu(k) % mod);
	}
	return Hash[x] = ret;
}
inline int calc_imu(LL L, LL R)
{
	int ret = calc_imu(R);
	dec(ret, calc_imu(L - 1));
	return ret;
}
int calc_g(LL n)
{
	int ret = 0;
	for(LL i = 1, j, k; i <= n; i = j + 1)
	{
		k = n / i;
		j = n / k;
		inc(ret, (j - i + 1) % mod * num1(k) % mod);
	}
	return ret;
}
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
		{
			prime[tot++] = d[i] = i;
			dec(f[i], 1);
		}
		for(int j = 0, k = (maxn - 1) / i, o; prime[j] <= k; ++j)
		{
			d[o = i * prime[j]] = prime[j];
			if(d[i] == prime[j])
			{
				f[o] = 0;
				break;
			}
			else
				dec(f[o], f[i]);
		}
		f[i] = (f[i - 1] + (LL)i * f[i]) % mod;
	}
	for(LL n; scanf("%lld", &n) == 1; )
	{
		int ans = 0;
		map<LL, int>().swap(Hash);
		for(LL i = 1, j, k; i <= n; i = j + 1)
		{
			k = n / i;
			j = n / k;
			int tmp = calc_g(k);
			inc(ans, (LL)calc_imu(i, j) * tmp % mod * tmp % mod);
		}
		printf("%d\n", ans);
	}
	return 0;
}
