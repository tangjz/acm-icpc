#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e6 + 1, mod = 998244353;
int n, m, q, inv[maxn];
inline int mod_inv(int x) {
	return x < n + m ? inv[x] : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	inv[1] = 1;
	for(int i = 2; i < n + m; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	int pos = q >> 1, val = 1;
	for(int i = 1; i < n + m; ++i)
		val = (LL)val * (pos + i) % mod * inv[i] % mod;
	int ans = 0, coeff = 1;
	for(int i = 0; i <= n; ++i) {
		for( ; pos && i + pos + pos > q; --pos)
			val = (LL)val * pos % mod * mod_inv(pos + n + m - 1) % mod;
		if(i + pos + pos == q)
			ans = (ans + (LL)coeff * val) % mod;
		coeff = (LL)coeff * (n - i) % mod * inv[i + 1] % mod;
	}
	printf("%d\n", ans);
	return 0;
}