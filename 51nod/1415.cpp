#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int mod = (int)1e9 + 7, inv2 = (mod + 1) >> 1;
int t, ans;
LL a, b, c, r, ab, ac, bc;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%lld%lld%lld", &a, &b, &c);
		r = std::__gcd(a, std::__gcd(b, c));
		a /= r;
		b /= r;
		c /= r;
		ab = std::__gcd(a, b) % mod;
		ac = std::__gcd(a, c) % mod;
		bc = std::__gcd(b, c) % mod;
		a %= mod;
		b %= mod;
		c %= mod;
		r %= mod;
		ans = (a * b + a * c + b * c - ab * ac % mod * bc) % mod * inv2 % mod * r % mod * r % mod;
		printf("%d\n", ans < 0 ? ans + mod : ans);
	}
	return 0;
}
