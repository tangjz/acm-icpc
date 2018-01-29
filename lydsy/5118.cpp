#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mod = 1125899839733759; // mod is prime, legendre(5, mod) == 1
LL n, v, x, y, a, b, c;
inline LL mod_add(LL x, LL y, LL m) {
	return (x += y) < m ? x : x - m;
}
inline LL mod_mul(LL x, LL y, LL m) {
	LL ret = 0;
	if(x < y)
		swap(x, y);
	for( ; y; y >>= 13, x = (x << 13) % m)
		(y & 8191) && (ret = (ret + x * (y & 8191)) % m);
	return ret;
}
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld", &y);
		for(n = 1, x = 2; y; y >>= 1, x = mod_mul(x, x, mod - 1))
			(y & 1) && (n = mod_mul(n, x, mod - 1));
		for(v = 1; v <= n; v <<= 1);
		for(x = 1, y = 0; (v >>= 1); ) {
			if(x != 1 || y != 0) {
				a = x;
				b = y;
				c = mod_mul(b, b, mod);
				x = mod_add(mod_mul(a, a, mod), c, mod);
				y = mod_mul(a, b, mod);
				y = mod_add(mod_add(y, y, mod), c, mod);
			}
			if(n & v) {
				c = mod_add(x, y, mod);
				x = y;
				y = c;
			}
		}
		printf("%lld\n", y);
	}
	return 0;
}
