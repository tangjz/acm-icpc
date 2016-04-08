#include <map>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1000010, mod = 1000000007, inv2 = 500000004;
map<LL, int> Hash;
int n, sqn, tot, prime[maxn], f[maxn], ans;
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
inline int num1(int x)
{
	return x * (x + 1LL) % mod * inv2 % mod;
}
inline int num1(int L, int R)
{
	int ret = num1(R);
	dec(ret, num1(L - 1));
	return ret;
}
int calc_imu(int x)
{
	if(x <= sqn)
		return f[x];
	if(Hash.count(x))
		return Hash[x];
	int ret = 1;
	for(int i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		dec(ret, (LL)num1(i, j) * calc_imu(x / i) % mod);
	}
	return Hash[x] = ret;
}
inline int calc_imu(int L, int R)
{
	int ret = calc_imu(R);
	dec(ret, calc_imu(L - 1));
	return ret;
}
int calc_g(int n)
{
	int ret = 0;
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		inc(ret, (j - i + 1LL) * num1(n / i) % mod);
	}
	return ret;
}
int calc_h(int n)
{
	int ret = 0;
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		inc(ret, (LL)(n / i) * num1(i, j) % mod);
	}
	return ret;
}
int main()
{
	scanf("%d", &n);
	sqn = (int)ceil(pow(n, 2.0 / 3));
	f[1] = 1;
	for(int i = 2; i <= sqn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			dec(f[i], 1);
		}
		for(int j = 0, k = sqn / i, o; j < tot && prime[j] <= k; ++j)
		{
			vis[o = i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				f[o] = 0;
				break;
			}
			else
				dec(f[o], f[i]);
		}
		f[i] = (f[i - 1] + (LL)i * f[i]) % mod;
	}
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		inc(ans, (LL)calc_imu(i, j) * calc_g(n / i) % mod * calc_g(n / i) % mod);
	}
	printf("%d\n", ans);
	return 0;
}
