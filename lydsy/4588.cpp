#include <stdio.h>
typedef long long LL;
const int maxn = 50, mod = 1000000007;
int iact[maxn], deg, val[maxn];
inline int mod_add(int x, int y)
{
	return x + y < mod ? x + y : x + y - mod;
}
int value(int x)
{
	if(x < deg)
		return val[x];
	static int pre[maxn], suf[maxn];
	pre[0] = x;
	for(int i = 1; i < deg; ++i)
		pre[i] = (LL)(x - i) * pre[i - 1] % mod;
	suf[deg - 1] = x - deg + 1;
	for(int i = deg - 2; i >= 0; --i)
		suf[i] = (LL)(x - i) * suf[i + 1] % mod;
	int ret = 0;
	for(int i = 0; i < deg; ++i)
	{
		int tmp = (LL)val[i] * iact[i] % mod * iact[deg - 1 - i] % mod;
		if(i > 0)
			tmp = (LL)tmp * pre[i - 1] % mod;
		if(i < deg - 1)
			tmp = (LL)tmp * suf[i + 1] % mod;
		if(((deg - 1 - i) & 1) && tmp > 0)
			tmp = mod - tmp;
		ret += tmp;
		if(ret >= mod)
			ret -= mod;
	}
	return ret;
}
void trans(int delta, int pos)
{
	static int nxt[maxn];
	for(int i = 0; i <= deg; ++i, pos = mod_add(pos, delta))
		nxt[i] = i > 0 ? mod_add(nxt[i - 1], value(pos)) : value(pos);
	++deg;
	for(int i = 0; i < deg; ++i)
		val[i] = nxt[i];
}
int n;
LL sum, values[maxn];
int main()
{
	iact[0] = 0;
	iact[1] = 1;
		for(int i = 2; i < maxn; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		iact[i] = iact[i - 1] * (LL)iact[i] % mod;
	while(scanf("%d%lld", &n, &sum) == 2)
	{
		for(int i = 0; i < n; ++i)
			scanf("%lld", values + i);
		deg = val[0] = 1;
		for(int i = 1; i < n; ++i)
		{
			LL delta = values[i] / values[i - 1];
			trans(delta % mod, sum % delta % mod);
			sum /= delta;
		}
		printf("%d\n", value(sum % mod));
	}
	return 0;
}
