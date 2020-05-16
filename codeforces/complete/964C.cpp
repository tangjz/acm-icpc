#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e9 + 9;
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main() {
	int n, a, b, m;
	scanf("%d%d%d%d ", &n, &a, &b, &m);
	int x = (LL)b * mod_pow(a, mod - 2) % mod;
	int y = mod_pow(x, m);
	int z = y == 1 ? (n + 1) / m : (mod_pow(y, (n + 1) / m) - 1LL) * mod_pow(y - 1, mod - 2) % mod;
	int ans = 0;
	for(int i = 0; i < m; ++i) {
		char ch;
		scanf("%c", &ch);
		if(ch == '+') {
			(ans += z) >= mod && (ans -= mod);
		} else {
			(ans -= z) < 0 && (ans += mod);
		}
		z = (LL)z * x % mod;
	}
	ans = (LL)ans * mod_pow(a, n) % mod;
	printf("%d\n", ans);
	return 0;
}