#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 9, mod = (int)1e9 + 7;
int tot, pr[maxn], d[maxn], iact[maxn], deg, val[maxn];
int n, a[maxn], ans;
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int value(int x) {
	if(x <= deg)
		return val[x];
	static int pre[maxn], suf[maxn];
	pre[0] = x % mod;
	for(int i = 1; i <= deg; ++i)
		pre[i] = (LL)(x - i) * pre[i - 1] % mod;
	suf[deg] = (x - deg) % mod;
	for(int i = deg - 1; i >= 0; --i)
		suf[i] = (LL)(x - i) * suf[i + 1] % mod;
	int ret = 0;
	for(int i = 0; i <= deg; ++i) {
		int tmp = (LL)val[i] * iact[i] % mod * iact[deg - i] % mod;
		i > 0 && (tmp = (LL)tmp * pre[i - 1] % mod);
		i < deg && (tmp = (LL)tmp * suf[i + 1] % mod);
		((deg - i) & 1) && tmp && (tmp = mod - tmp);
		(ret += tmp) >= mod && (ret -= mod);
	}
	return ret;
}
int main() {
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	while(scanf("%d", &n) == 1) {
		a[0] = ans = 1;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			ans = (LL)ans * a[i] % mod;
		}
		sort(a + 1, a + n + 1);
		ans = (LL)ans * a[n] % mod;
		for(int i = 1, prd = 1; i <= n; prd = (LL)prd * a[i++] % mod) {
			if(a[i - 1] == a[i])
				continue;
			int k = n - i + 1;
			deg = k + 1;
			memset(val, 0, (deg + 1) * sizeof(int));
			val[1] = 1;
			for(int j = 2; j <= deg; ++j)
				if(d[j] == j)
					val[j] = mod_pow(j, k);
				else
					val[j] = (LL)val[d[j]] * val[j / d[j]] % mod;
			for(int j = 1; j <= deg; ++j)
				(val[j] += val[j - 1]) >= mod && (val[j] -= mod);
			int coeff = value(a[i - 1] - 1) - value(a[i] - 1);
			coeff < 0 && (coeff += mod);
			ans = (ans + (LL)coeff * prd) % mod;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
