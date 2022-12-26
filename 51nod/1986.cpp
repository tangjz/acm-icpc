#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e9 + 7, maxm = (int)1e8 + 1, maxs = (int)2e4 + 1, maxm2 = (int)3.5e5 + 1;
int t, n, m, m2, sq, a[maxs], b[maxs], fct[maxs], ifct[maxs], cff[maxs], icff[maxs];
int tot, pr[maxm >> 3 | 1], crb[maxm], f[maxm2], g[maxm2];
inline int mod_inv(int x, int p) {
	int y = p, u = 1, v = 0;
	while(y) {
		int r = x / y;
		swap(x, y);
		y -= r * x;
		swap(u, v);
		v -= r * u;
	}
	return u < 0 ? u + p : u;
}
inline int mod_pow(int x, int k, int p) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		(k & 1) && (ret = (LL)ret * x % p);
	return ret;
}
inline int idx(int v) {
	return v <= sq ? v - 1 : sq + sq - m / v;
}
inline int rdx(int x) {
	return x < sq ? x + 1 : m / (sq + sq - x);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		m2 = max((int)ceil(pow(m + m, 2.0 / 3)), 1);
		tot = 0;
		memset(crb + 1, 0, m * sizeof(int));
		crb[1] = f[1] = g[1] = 1;
		for(int i = 2; i <= m; ++i) {
			if(!crb[i]) {
				pr[tot++] = crb[i] = i;
				if(i <= m2)
					f[i] = i - 1;
			}
			for(int j = 0, k; (k = i * pr[j]) <= m; ++j) {
				crb[k] = pr[j];
				if(k <= m2)
					f[k] = f[i] * (crb[i] == pr[j] ? pr[j] : pr[j] - 1);
				if(crb[i] == pr[j])
					break;
			}
			if(crb[i] < i)
				crb[i] = crb[i / crb[i]] == crb[i] ? crb[i] : 1;
			if(i <= m2) {
				g[i] = (LL)g[i - 1] * mod_pow(i, f[i], mod) % mod;
				(f[i] += f[i - 1]) >= mod - 1 && (f[i] -= mod - 1);
			}
		}
		for(sq = 1; sq * sq <= m; ++sq);
		--sq;
		int fact = 1, prod = 1, coeff = 1, last = 1;
		for(int i = 0; i < sq + sq; ++i) {
			int d = rdx(i);
			if(i >= sq && d <= sq)
				continue;
			for( ; last <= d; ++last) {
				prod = (LL)prod * fact % mod;
				fact = (LL)fact * last % mod;
				coeff = (LL)coeff * crb[last] % mod;
			}
			fct[i] = fact;
			ifct[i] = mod_inv(fact, mod);
			cff[i] = coeff;
			icff[i] = mod_inv(coeff, mod);
			if(d <= m2) {
				a[i] = f[d];
				b[i] = g[d];
			} else {
				a[i] = 0;
				b[i] = 1;
				for(int x = 1, y, k, las = 0; x < d; x = y) {
					k = d / (x + 1);
					y = d / k;
					int pos = idx(k), cur = idx(y);
					a[i] = (a[i] + (LL)(y - x) * a[pos]) % (mod - 1);
					b[i] = (LL)b[i] * mod_pow((LL)fct[cur] * ifct[las] % mod, a[pos], mod) % mod * mod_pow(b[pos], y - x, mod) % mod;
					las = cur;
				}
				(a[i] = (d * (d + 1LL) / 2 - a[i]) % (mod - 1)) < 0 && (a[i] += mod - 1);
				b[i] = (LL)mod_pow(fact, d, mod) * mod_inv((LL)prod * b[i] % mod, mod) % mod;
			}
		}
		int ans = 1;
		for(int x = 0, y, k, las = -1; x < m; x = y) {
			k = m / (x + 1);
			y = m / k;
			int tmp = 1, pwk = mod_pow(k, n, mod - 1);
			for(int L = 1, R, d, las2 = 0; L < k; L = R) {
				d = k / (L + 1);
				R = k / d;
				int cur2 = idx(R), ex = pwk - mod_pow(k - d, n, mod - 1);
				tmp = (LL)tmp * mod_pow((LL)cff[cur2] * icff[las2] % mod, ex < 0 ? ex + mod - 1 : ex, mod) % mod;
				las2 = cur2;
			}
			int cur = idx(y), ex = a[cur] - (las >= 0 ? a[las] : 0);
			ans = (LL)ans * mod_pow(tmp, ex < 0 ? ex + mod - 1 : ex, mod) % mod * mod_pow((LL)b[cur] * mod_inv(las >= 0 ? b[las] : 1, mod) % mod, pwk, mod) % mod;
			las = cur;
		}
		printf("%d\n", ans);
	}
	return 0;
}
