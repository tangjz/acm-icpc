#include <bits/stdc++.h>
typedef long long LL;
const int mod = (int)1e9 + 7, inv6 = (mod + 1) / 6;
int main() {
	LL n;
	scanf("%lld", &n);
	int ans = 0, nn = n % mod;
	int f0 = nn * (nn + 1LL) % mod * (nn + 2) % mod, f1 = (3LL * nn + 4) % mod, f2 = mod - 3LL * (nn + 2) % mod, f3 = 2;
	int g0 = 0, g1 = 0, g2 = 0, g3 = 0, x, y;
	for(x = 0; (LL)x * x <= n; ++x);
	for(--x, y = 1; x >= 0; --x) {
		for(LL rem = n - (LL)x * x; (LL)y * y <= rem; ++y) {
			int y2 = (LL)y * y % mod, y4 = (LL)y2 * y2 % mod, y6 = (LL)y2 * y4 % mod;
			(++g0) >= mod && (g0 -= mod);
			(g1 += y2) >= mod && (g1 -= mod);
			(g2 += y4) >= mod && (g2 -= mod);
			(g3 += y6) >= mod && (g3 -= mod);
		}
		int x2 = (LL)x * x % mod, x4 = (LL)x2 * x2 % mod, x6 = (LL)x2 * x4 % mod;
		int sum = ((f0 + (LL)f1 * x2 + (LL)f2 * x4 + (LL)f3 * x6) % mod * (g0 << 1 | 1)
			+ (f1 + 2LL * f2 * x2 + 3LL * f3 * x4) % mod * (g1 << 1)
			+ (f2 + 3LL * f3 * x2) % mod * (g2 << 1)
			+ (LL)f3 * (g3 << 1)) % mod;
		x && (sum <<= 1) >= mod && (sum -= mod);
		(ans += sum) >= mod && (ans -= mod);
	}
	ans = (LL)ans * inv6 % mod;
	printf("%d\n", ans);
	return 0;
}
