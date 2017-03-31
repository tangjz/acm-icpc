#include <cmath>
#include <cstdio>
#include <unordered_map>
using namespace std;
typedef long long LL;
const int maxn = 1000010, mod = 1000000007;
unordered_map<LL, int> Hash;
int n, sqn, tot, prime[maxn], d[maxn], dk[maxn], e[maxn], f[maxn], g[maxn], ans;
inline void inc(int &x, int y)
{
	if((x += y) >= mod)
		x -= mod;
}
inline void dec(int &x, int y)
{
	if((x -= y) < 0)
		x += mod;
}
inline int num1(int x)
{
	return (x * (x + 1LL) >> 1) % mod;
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
	static int last = 0;
	int cur = calc_imu(R), ret = cur;
	dec(ret, last);
	last = cur;
	return ret;
}
int calc_g(int n)
{
	if(n <= sqn)
		return g[n];
	int ret = 0;
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		inc(ret, (j - i + 1LL) * num1(n / i) % mod);
	}
	return ret;
}
inline int sqr(int x)
{
	return (LL)x * x % mod;
}
int main()
{
	scanf("%d", &n);
	sqn = (int)ceil(pow(n, 2.0 / 3));
	f[1] = g[1] = 1;
	for(int i = 2; i <= sqn; ++i)
	{
		if(!d[i])
		{
			prime[tot++] = d[i] = dk[i] = i;
			e[i] = 1;
			dec(f[i], 1);
			g[i] = i + 1;
		}
		for(int j = 0, k; (k = i * prime[j]) <= sqn; ++j)
		{ // d, dk, e, g
			d[k] = prime[j];
			if(d[i] == prime[j])
			{
				dk[k] = dk[i] * prime[j];
				e[k] = e[i];
				f[k] = 0;
				g[k] = e[k] == 1 ? ((LL)g[i] * prime[j] + 1) % mod : (LL)g[dk[k]] * g[e[i]] % mod;
				break;
			}
			else
			{
				dk[k] = prime[j];
				e[k] = i;
				dec(f[k], f[i]);
				g[k] = (LL)g[i] * (prime[j] + 1) % mod;
			}
		}
		f[i] = (f[i - 1] + (LL)i * f[i]) % mod;
	}
	for(int i = 2; i <= sqn; ++i)
		inc(g[i], g[i - 1]);
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		inc(ans, (LL)calc_imu(i, j) * sqr(calc_g(n / i)) % mod);
	}
	printf("%d\n", ans);
	return 0;
}
