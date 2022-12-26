#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1001, mod = 998244353;
int n, m, f[maxn], g[maxn], ans;
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	f[1] = 1;
	for(int i = 2; i <= n; ++i)
		f[i] = mod - (int)(mod / i * (LL)f[mod % i] % mod);
	f[0] = 1;
	for(int i = 1; i <= n; ++i)
		f[i] = (LL)f[i - 1] * f[i] % mod;
	for(int i = 1; i <= n; ++i)
		f[i] = mod_pow(f[i], m);
	g[0] = 1;
	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j < i; ++j)
			g[i] = (g[i] + ((i - j) & 1 ? 1LL : -1LL) * g[j] * f[i - j]) % mod;
		g[i] < 0 && (g[i] += mod);
	}
	int ans = g[n];
	for(int i = 1; i <= n; ++i)
		ans = (LL)ans * i % mod;
	printf("%d\n", ans);
	return 0;
}
