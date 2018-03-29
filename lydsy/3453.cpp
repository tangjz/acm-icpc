#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 129, mod = 1234567891;
int iact[maxn], deg, val[maxn], f[maxn];
int value(LL x) {
	if(x <= deg)
		return val[(int)x];
	static int pre[maxn], suf[maxn];
	pre[0] = x % mod;
	for(int i = 1; i <= deg; ++i)
		pre[i] = (x - i) % mod * pre[i - 1] % mod;
	suf[deg] = (x - deg) % mod;
	for(int i = deg - 1; i >= 0; --i)
		suf[i] = (x - i) % mod * suf[i + 1] % mod;
	int ret = 0;
	for(int i = 0; i <= deg; ++i) {
		int tmp = (LL)val[i] * iact[i] % mod * iact[deg - i] % mod;
		i > 0 && (tmp = (LL)tmp * pre[i - 1] % mod);
		i < deg && (tmp = (LL)tmp * suf[i + 1] % mod);
		((deg - i) & 1) && tmp && (tmp = mod - tmp);
		(ret += tmp - mod) < 0 && (ret += mod);
	}
	return ret;
}
int main() {
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (mod / i * (LL)iact[mod % i] % mod);
	iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	int t, k, a, n, d;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d", &k, &a, &n, &d);
		deg = k + 2;
		f[0] = val[0] = 0;
		for(int i = 1; i <= deg; ++i) {
			f[i] = 1;
			for(int j = 1; j <= k; ++j)
				f[i] = (LL)f[i] * i % mod;
			(f[i] += f[i - 1] - mod) < 0 && (f[i] += mod);
		}
		for(int i = 1; i <= deg; ++i)
			(val[i] = val[i - 1] + f[i] - mod) < 0 && (val[i] += mod);
		for(int i = 0; i <= deg + 1; ++i)
			f[i] = value(a + (LL)i * d);
		++deg;
		val[0] = f[0];
		for(int i = 1; i <= deg; ++i)
			(val[i] = val[i - 1] + f[i] - mod) < 0 && (val[i] += mod);
		printf("%d\n", value(n));
	}
	return 0;
}
