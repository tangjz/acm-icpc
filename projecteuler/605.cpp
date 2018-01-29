#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e8;
int mod_inv(int x, int p) {
    int y = p, u = 1, v = 0, r;
    while(y) {
    	r = x / y;
    	swap(x, y);
    	y -= r * x;
    	swap(u, v);
    	v -= r * u;
    }
    assert(x == 1);
	return u < 0 ? u + p : u;
}
int mod_pow(int x, int k, int p) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		(k & 1) && (ret = (LL)ret * x % p);
	return ret;
}
int main() {
	int n, k;
	while(scanf("%d%d", &n, &k) == 2) {
		int com = __gcd(n, mod_pow(2, n, n) - 1), inv = mod_inv(com, mod), tmp = mod_pow(2, n, mod) - 1;
		tmp < 0 && (tmp += mod);
		int ans = (LL)mod_pow(2, n - k, mod) * ((LL)tmp * (k - 1) % mod + n) % mod * tmp % mod * tmp % mod * inv % mod * inv % mod;
		printf("%d\n", ans);
	}
	return 0;
}
