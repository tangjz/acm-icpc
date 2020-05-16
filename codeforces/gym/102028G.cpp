#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1, maxLen = 19, maxm = 1 << maxLen | 1, mod = 998244353, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxm], f[maxm], g[maxm];
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : x - mod;
}
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}
inline int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; x = (LL)x * x % mod, k >>= 1)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
void NTT_init() {
	w[0] = 1; // make sure that mod = 2 ^ maxLen * k + 1
	w[1] = mod_pow(gen, (mod - 1) >> maxLen);
	for(int i = 2; i < maxm; ++i) // w[1 << maxLen] = 1
		w[i] = (LL)w[i - 1] * w[1] % mod;
}
void NTT(int len, int x[], int flag) {
	static int bitLen = 0, ivs = 1, bitRev[maxm] = {};
	if(len != (1 << bitLen)) {
		for(bitLen = 0, ivs = 1; 1 << bitLen < len; ++bitLen, ivs = (LL)ivs * inv2 % mod);
		for(int i = 1; i < len; ++i)
		    bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
	}
	for(int i = 1; i < len; ++i)
		if(i < bitRev[i])
			swap(x[i], x[bitRev[i]]);
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d << 1)
			for(int k = 0, *X = x + j; k < d; ++k) {
				int tmp = (LL)w[k << (maxLen - i)] * X[k + d] % mod;
				X[d + k] = mod_sub(X[k], tmp);
				X[k] = mod_add(X[k], tmp);
			}
	if(flag == -1) {
		reverse(x + 1, x + len);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * ivs % mod;
	}
}
void poly_mul(int n, int a[], int b[], int c[]) { // c = a * b (mod x^n)
	int len;
	for(len = 1; len <= (n - 1) << 1; len <<= 1);
	memcpy(f, a, n * sizeof(int));
	memset(f + n, 0, (len - n) * sizeof(int));
	memcpy(g, b, n * sizeof(int));
	memset(g + n, 0, (len - n) * sizeof(int));
	NTT(len, f, 1);
	NTT(len, g, 1);
	for(int i = 0; i < len; ++i)
		f[i] = (LL)f[i] * g[i] % mod;
	NTT(len, f, -1);
	memcpy(c, f, n * sizeof(int));
}
int inv[maxn], a[maxn], b[maxn], c[maxn];
int mod_inv(int x) {
	return x < maxn ? inv[x] : (mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod));
}
void solve(int L, int R) {
	if(L == R) {
		c[L] = L ? (LL)c[L] * inv[L] % mod : 1;
		return;
	}
	int M = (L + R) >> 1;
	solve(L, M);
	int len, lft = R - L, rht = M - L + 1;
	for(len = 1; len < lft; len <<= 1);
	memcpy(f, a, lft * sizeof(int));
	memset(f + lft, 0, (len - lft) * sizeof(int));
	memcpy(g, c + L, rht * sizeof(int));
	memset(g + rht, 0, (len - rht) * sizeof(int));
	NTT(len, f, 1);
	NTT(len, g, 1);
	for(int i = 0; i < len; ++i)
		f[i] = (LL)f[i] * g[i] % mod;
	NTT(len, f, -1);
	for(int i = M + 1, j = i - L - 1; i <= R; ++i, ++j)
		(c[i] += f[j]) >= mod && (c[i] -= mod);
	solve(M + 1, R);
}
int main() {
	NTT_init();
	a[0] = 0;
	inv[1] = a[1] = 1;
	for(int i = 2, ivs = 1; i < maxn; ++i) {
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		ivs = (LL)ivs * inv[i] % mod;
		a[i] = (LL)mod_pow(i, i) * ivs % mod;
	}
	poly_mul(maxn, a, a, b);
	poly_mul(maxn, a, b, a);
	for(int i = 0; i < maxn; ++i)
		b[i] = ((LL)b[i] * inv2 + a[i]) % mod;
	a[0] = 1;
	for(int i = 1, ivs = 1; i < maxn; ++i) {
		ivs = (LL)ivs * inv[i] % mod;
		a[i] = (LL)mod_pow(i + 1, i - 1) * ivs % mod;
	}
	solve(0, maxn - 1);
	for(int i = maxn - 1; i > 0; --i)
		a[i] = (i - 1LL) * inv2 % mod * a[i - 1] % mod;
	a[0] = 0;
	poly_mul(maxn, a, c, a);
	for(int i = 0; i < maxn; ++i)
		(a[i] = (i * (i - 1LL) / 2 % mod * c[i] - a[i]) %  mod) < 0 && (a[i] += mod);
	poly_mul(maxn, b, c, b);
	int t, n, m;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		assert(c[n] != 0);
		int ans = ((LL)m * m % mod * a[n] + b[n]) % mod * mod_inv(c[n]) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
