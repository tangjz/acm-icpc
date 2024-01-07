#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, maxs = (int)1e3 + 1;
int tot, pr[maxn >> 3 | 1], d[maxn], n;
LL f[maxn];
__int128_t g[maxs];
inline LL num1(int L, int R) {
	return (L + R) * (R - L + 1LL) / 2;
}
__int128_t calc_iphi(int x) {
	if(x < maxn)
		return f[x];
	__int128_t &ret = g[n / x];
	if(ret == -1) {
		ret = x * (x + 1LL) * (__int128_t)(x + x + 1) / 6;
		for(int i = 2, j; i <= x; i = j + 1) {
			j = x / (x / i);
			ret -= calc_iphi(x / i) * num1(i, j);
		}
	}
	return ret;
}
int main() {
	d[1] = f[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			f[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			f[k] = f[i] * pr[j];
			if(d[i] == pr[j])
				break;
			f[k] -= f[i];
		}
		f[i] = f[i - 1] + i * f[i];
	}
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%*d%*d", &n);
		if(n >= maxn)
			memset(g, -1, (n / maxn + 1) * sizeof(__int128_t));
		__int128_t ans = (calc_iphi(n) - 1) >> 1;
		const int mod = (int)1e9 + 7;
		printf("%d\n", (int)(ans % mod));
	}
	return 0;
}