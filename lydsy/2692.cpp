#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e3 + 1, mod = (int)1e9 + 7;
int inv[maxn], a[maxn], b[maxn], c[maxn], d[maxn], a2[maxn], b2[maxn], d2[maxn];
int da2[maxn], db[maxn], db2[maxn], dc[maxn], dd[maxn], dd2[maxn];
int sa2[maxn], sb[maxn], sb2[maxn], sc[maxn], sd[maxn], sd2[maxn], ans[maxn];
inline void mod_inc(LL &x, LL y) {
	if(x + y < 0)
		x %= mod;
	x += y;
}
inline LL mod_fix(LL x) {
	return x < mod ? x : x % mod;
}
int main() {
	inv[1] = a[1] = b[1] = c[1] = d[1] = db[1] = dc[1] = dd[1] = ans[1] = 1;
	a2[1] = b2[1] = d2[1] = da2[1] = db2[1] = dd2[1] = 2;
	for(int i = 2; i < maxn; ++i) {
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		LL tsa2 = 0, tsb = 0, tsb2 = 0, tsc = 0, tsd = 0, tsd2 = 0;
		for(int j = 1; j < i; ++j) {
			mod_inc(tsa2, (LL)da2[j] * (a2[i - j] + sa2[i - j]));
			mod_inc(tsb, (LL)db[j] * (b[i - j] + sb[i - j]));
			mod_inc(tsb2, (LL)db2[j] * (b2[i - j] + sb2[i - j]));
			mod_inc(tsc, (LL)dc[j] * (c[i - j] + sc[i - j]));
			mod_inc(tsd, (LL)dd[j] * (d[i - j] + sd[i - j]));
			mod_inc(tsd2, (LL)dd2[j] * (d2[i - j] + sd2[i - j]));
		}
		sa2[i] = mod_fix(tsa2) * inv[i] % mod;
		sb[i] = mod_fix(tsb) * inv[i] % mod;
		sb2[i] = mod_fix(tsb2) * inv[i] % mod;
		sc[i] = mod_fix(tsc) * inv[i] % mod;
		sd[i] = mod_fix(tsd) * inv[i] % mod;
		sd2[i] = mod_fix(tsd2) * inv[i] % mod;
		(a[i] = sb2[i] - sb[i]) < 0 && (a[i] += mod);
		b[i] = (LL)sa2[i] * inv[2] % mod;
		(c[i] = sd2[i] - sd[i]) < 0 && (c[i] += mod);
		d[i] = sc[i];
		(a2[i] = a[i] << 1) >= mod && (a2[i] -= mod);
		(b2[i] = b[i] << 1) >= mod && (b2[i] -= mod);
		(d2[i] = d[i] << 1) >= mod && (d2[i] -= mod);
		da2[i] = (LL)i * a2[i] % mod;
		db[i] = (LL)i * b[i] % mod;
		db2[i] = (LL)i * b2[i] % mod;
		dc[i] = (LL)i * c[i] % mod;
		dd[i] = (LL)i * d[i] % mod;
		dd2[i] = (LL)i * d2[i] % mod;
	}
	for(int i = 2, prd = 1; i < maxn; ++i) {
		(ans[i] += a2[i]) >= mod && (ans[i] -= mod);
		(ans[i] += b2[i]) >= mod && (ans[i] -= mod);
		(ans[i] -= c[i]) < 0 && (ans[i] += mod);
		(ans[i] -= d[i]) < 0 && (ans[i] += mod);
		prd = (LL)prd * i % mod;
		ans[i] = (LL)ans[i] * prd % mod;
	}
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}
