#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7, inv2 = (mod + 1) >> 1;
int n, m, a[maxn], ans;
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		scanf("%d", a + i);
	sort(a, a + m);
	for(int i = 0; i < m; ++i) {
		int L = ((LL)i * n + 1) % mod, R = ((i + 1LL) * n) % mod;
		int sum = (L + R) * (R - L + 1LL) % mod * inv2 % mod;
		a[i] %= mod;
		if(a[i] == 1) {
			ans = (ans + (LL)n * sum) % mod;
		} else {
			int prd = a[i] ? (mod_pow(a[i], n) - 1LL) * mod_pow(a[i] - 1, mod - 2) % mod : 1;
			ans = (ans + (LL)prd * sum) % mod;
		}
	}
	printf("%d\n", ans);
	return 0;
}
