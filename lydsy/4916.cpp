#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 6068321, maxs = 31623, mod = 1000000007, inv6 = (mod + 1) / 6;
int tot, pr[maxn], d[maxn], f[maxn];
int n, sz, fact[maxs], g[maxs], ans;
inline void inc(int &x, int y)
{
	(x += y) >= mod && (x -= mod);
}
inline void dec(int &x, int y)
{
	(x -= y) < 0 && (x += mod);
}
inline int num1(int L, int R)
{
	return ((L + R) * (R - L + 1LL) >> 1) % mod;
}
int calc_iphi(int x)
{
	if(x < maxn)
		return f[x];
	int idx = lower_bound(fact, fact + sz, x) - fact;
	if(g[idx] >= 0)
		return g[idx];
	int ret = x * (x + 1LL) % mod * ((x << 1) + 1) % mod * inv6 % mod;
	for(int i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		dec(ret, (LL)calc_iphi(x / i) * num1(i, j) % mod);
	}
	return g[idx] = ret;
}
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = i;
			f[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
			{
				f[k] = f[i] * pr[j];
				break;
			}
			else
				f[k] = f[i] * (pr[j] - 1);
		}
		f[i] = (f[i - 1] + (LL)i * f[i]) % mod;
	}
	scanf("%d", &n);
	for(int i = 1; (LL)i * i <= n; ++i)
		fact[sz++] = n / i;
	reverse(fact, fact + sz);
	memset(g, -1, sz * sizeof(int));
	printf("1\n%d\n", calc_iphi(n));
	return 0;
}
