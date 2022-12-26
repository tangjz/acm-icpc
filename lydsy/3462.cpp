#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)2e6 + 1, mod = (int)1e9 + 7, maxe = 7, maxs = (maxn - 1) * maxe + 1;
int n, cnt, sum, pr[maxe], deg, poly[maxs], inv[maxn];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
inline void mod_inc_mul(int &x, int y, int z) {
	y && z && (x = (x + (LL)y * z) % mod);
}
inline int mod_inv(int x) {
	return x < n ? inv[x] : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main() {
	int t;
	scanf("%d%d", &n, &t);
	for(int i = 2, tmp = n; i <= tmp; ++i) {
		if(i * i > tmp)
			i = tmp;
		if(tmp % i == 0) {
			tmp /= i;
			if(tmp % i == 0) {
				while(t--)
					puts("0");
				return 0;
			}
			pr[cnt++] = i;
			sum += i;
			deg += n - i;
		}
	}
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	for(int i = 0, j = 0, coeff = 1; i <= deg; i += n, ++j) {
		poly[i] = j & 1 ? mod - coeff : coeff;
		coeff = (LL)coeff * (cnt - j) % mod * mod_inv(j + 1) % mod;
	}
	for(int i = 0; i < cnt; ++i)
		for(int j = pr[i]; j <= deg; ++j)
			mod_inc(poly[j], poly[j - pr[i]]);
	while(t--) {
		LL x;
		scanf("%lld", &x);
		x -= sum;
		int r = x % n;
		if(x < 0 || deg < r) {
			puts("0");
			continue;
		}
		x /= n;
		int ans = 0, coeff = 1;
		LL pos = std::max(x - (deg - r) / n, 0LL);
		if(mod - pos % mod < cnt) {
			pos += mod - pos % mod;
			coeff = 1;
		} else {
			for(int i = 1; i < cnt; ++i)
				coeff = coeff * ((pos + i) % mod) % mod * mod_inv(i) % mod;
		}
		for( ; pos <= x; ++pos) {
			mod_inc_mul(ans, coeff, poly[(x - pos) * n + r]);
			if(mod - (pos + 1) % mod < cnt) {
				pos += mod - (pos + 1) % mod;
				coeff = 1;
			} else {
				coeff = coeff * ((pos + cnt) % mod) % mod * mod_inv((pos + 1) % mod) % mod;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
