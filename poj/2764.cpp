#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 5, maxl = 8 * 9 * 5 * 7 + 1, maxd = maxn * maxl + 1;
int n, lcm, w[maxn], deg;
LL low, poly[maxd];
inline LL safeAdd(LL x, LL y) {
	return (x += y) > low ? low + 1 : x;
}
inline LL safeMul(LL x, LL y) {
	return x && y && x > low / y ? low + 1 : x * y;
}
int chkRem(LL x) {
	static LL f[maxl];
	memset(f, 0, lcm * sizeof(LL));
	LL pos = std::max(x - deg / lcm, 0LL), coeff = 1;
	for(int i = 1; i < n && coeff <= low; ++i) {
		LL num = pos + i, den = i, com = std::__gcd(num, den);
		coeff = safeMul(coeff / (den / com), num / com);
	}
	for( ; pos <= x; ++pos) {
		for(int i = 0, j = (x - pos) * lcm; i < lcm && j <= deg; ++i, ++j)
			f[i] = safeAdd(f[i], safeMul(coeff, poly[j]));
		if(coeff <= low) {
			LL num = pos + n, den = pos + 1, com = std::__gcd(num, den);
			coeff = safeMul(coeff / (den / com), num / com);
		}
	}
	for(int i = !x; i < lcm; ++i)
		if(f[i] >= low)
			return i;
	return -1;
}
int main() {
	for(int Case = 1; scanf("%d", &n) == 1 && n > 0; ++Case) {
		printf("Set %d\n", Case);
		lcm = 1;
		deg = 0;
		for(int i = 0; i < n; ++i) {
			scanf("%d", w + i);
			lcm *= w[i] / std::__gcd(w[i], lcm);
			deg += w[i];
		}
		deg = n * lcm - deg;
		memset(poly, 0, (deg + 1) * sizeof(LL));
		for(int i = 0, j = 0, coeff = 1; i <= deg; i += lcm, ++j) {
			poly[i] = j & 1 ? -coeff : coeff;
			coeff = coeff * (n - j) / (j + 1);
		}
		for(int i = 0; i < n; ++i)
			for(int j = w[i]; j <= deg; ++j)
				poly[j] += poly[j - w[i]]; // poly[j] in [0, pow(lcm, n - 1)];
		int t;
		scanf("%d", &t);
		while(t--) {
			scanf("%lld", &low);
			int mx;
			LL x, ans = -1;
			for(mx = 0; ; ++mx) {
				x = (1LL << mx) - 1;
				ans = chkRem(x);
				if(ans != -1) {
					ans += x * lcm;
					break;
				} else if(x >= 100 * low) {
					break;
				}
			}
			if(ans == -1) {
				puts("no candy for you");
				continue;
			}
			for(int i = mx - 2; i >= 0; --i) {
				int rem = chkRem(x ^ (1LL << i));
				if(rem != -1) {
					x ^= 1LL << i;
					ans = x * lcm + rem;
				}
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}