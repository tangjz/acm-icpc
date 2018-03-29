#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 5001, mod = (int)1e9 + 7, inv2 = (mod + 1) / 2;
int n, m, a[maxn], s[maxn];
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	a[0] = s[0] = 1;
	for(int i = 1; i <= m; ++i) {
		a[i] = (LL)a[i - 1] * (n - i + 1LL) % mod;
		for(int j = i; j >= 1; --j)
			s[j] = (s[j - 1] + (LL)j * s[j]) % mod;
		s[0] = 0;
	}
	int ans = 0, prd = mod_pow(2, n);
	for(int i = 0; i <= m; ++i, prd = (LL)prd * inv2 % mod)
		ans = (ans + (LL)a[i] * s[i] % mod * prd) % mod;
	printf("%d\n", ans);
	return 0;
}
