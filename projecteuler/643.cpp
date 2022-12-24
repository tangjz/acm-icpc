#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 21544347, maxs = 4643, mod = (int)1e9 + 7;
int tot, d[maxn], pr[maxn], f[maxn], g[maxs];
LL n;
int calc_phi(LL x) {
	if(x < maxn)
		return f[x];
	int pos = n / x;
	if(g[pos] >= 0)
		return g[pos];
	int ret = x & 1 ? (x + 1) / 2 % mod * (x % mod) % mod : x / 2 % mod * ((x + 1) % mod) % mod;
	for(LL i = 1, j, k; i < x; i = j) {
		k = x / (i + 1);
		j = x / k;
		ret = (ret - (j - i) % mod * calc_phi(k)) % mod;
	}
	return g[pos] = ret < 0 ? ret + mod : ret;
}
int main() {
	f[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			f[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j]) {
				f[k] = f[i] * pr[j];
				break;
			}
			f[k] = f[i] * (pr[j] - 1);
		}
		(f[i] += f[i - 1]) >= mod && (f[i] -= mod);
	}
	while(scanf("%lld", &n) == 1) {
		int ans = 0;
		memset(g, -1, (n / maxn + 1) * sizeof(int));
		for(LL i = 2; i <= n; i <<= 1) {
			(ans += calc_phi(n / i)) >= mod && (ans -= mod);
			(--ans) < 0 && (ans += mod);
		}
		printf("%d\n", ans);
	}
	return 0;
}
