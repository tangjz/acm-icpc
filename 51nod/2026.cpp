#include <cmath>
#include <stdio.h>
#include <unordered_map>
typedef long long LL;
const int maxn = 1000001, maxs = 31623, mod = (int)1e9 + 7;
int n, m, tot, pr[maxn], d[maxn], f[maxn];
std::unordered_map<int, int> sf;
int calc(int n) {
	if(n <= m)
		return f[n];
	if(sf.count(n))
		return sf[n];
	int ret = n;
	for(int i = 2, j, k; i <= n; i = j) {
		k = n / i;
		j = n / k + 1;
		ret = (ret - (((i + j - 1LL) * (j - i)) >> 1) % mod * calc(k)) % mod;
	}
	return sf[n] = ret < 0 ? ret + mod : ret;
}
int main() {
	scanf("%d", &n);
	m = (int)ceil(pow(n, 2.0 / 3));
	for(int i = m + 1, j; i <= n; j = n / i, i = n / j + 1, ++tot);
	sf.reserve(tot);
	tot = 0;
	f[1] = 1;
	for(int i = 2; i <= m; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			f[i] = mod + 1 - i;
		}
		for(int j = 0, k; (k = i * pr[j]) <= m; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j]) {
				f[k] = f[i];
				break;
			}
			f[k] = (LL)f[i] * f[pr[j]] % mod;
		}
	}
	for(int i = 2; i <= m; ++i)
		(f[i] += f[i - 1]) >= mod && (f[i] -= mod);
	int ans = calc(n);
	printf("%d\n", (int)((LL)ans * ans % mod));
	return 0;
}
