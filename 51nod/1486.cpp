#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxa = 100010, maxd = 10, maxp = 2010, mod = 1000000007;
typedef long long LL;
int d, p, fact[maxa * maxd], inv[maxa], f[maxp];
struct Point
{
	int x[maxd];
	bool operator < (const Point &t) const
	{
		for(int i = 0; i < d; ++i)
			if(x[i] != t.x[i])
				return x[i] < t.x[i];
		return 0;
	}
} a[maxp];
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int calc(int s, int t)
{
	int ret = 1, tot = 0;
	for(int i = 0; i < d; ++i)
	{
		if(a[s].x[i] > a[t].x[i])
			return 0;
		tot += a[t].x[i] - a[s].x[i];
		ret = (LL)ret * inv[a[t].x[i] - a[s].x[i]] % mod;
	}
	ret = (LL)ret * fact[tot] % mod;
	return ret;
}
int main()
{
	fact[0] = 1;
	for(int i = 1; i < maxa * maxd; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	inv[0] = inv[1] = 1;
	for(int i = 2; i < maxa; ++i)
		inv[i] = (LL)inv[mod % i] * (mod - mod / i) % mod;
	for(int i = 2; i < maxa; ++i)
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	d = 2;
	int t1, t2;
	scanf("%d%d%d", &t1, &t2, &p);
	a[0].x[0] = a[0].x[1] = 1;
	a[p + 1].x[0] = t1;
	a[p + 1].x[1] = t2;
	for(int i = 1; i <= p; ++i)
		for(int j = 0; j < d; ++j)
			scanf("%d", a[i].x + j);
	sort(a + 1, a + p + 1);
	f[0] = 1;
	for(int i = 1; i <= p + 1; ++i)
	{
		f[i] = calc(0, i);
		for(int j = 1; j < i; ++j)
		{
			f[i] -= (LL)f[j] * calc(j, i) % mod;
			if(f[i] < 0)
				f[i] += mod;
		}
	}
	printf("%d\n", f[p + 1]);
	return 0;
}
