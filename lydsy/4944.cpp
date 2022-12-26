#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1003, mod = 998244353, maxLen = 11, maxs = 1 << maxLen | 1, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxs], A[maxs], B[maxs];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
}
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? (x + mod) : x;
}
void initNTT(int len) {
	int bitLen;
	for(bitLen = 0; (1 << bitLen) < len; ++bitLen);
	int *W = w + (1 << (bitLen - 1));
	W[0] = W[1] = 1;
	for(int i = (mod - 1) >> bitLen, x = gen; i > 0; i >>= 1, x = (LL)x * x % mod)
		if(i & 1)
			W[1] = (LL)W[1] * x % mod;
	for(int i = 2; i < (1 << (bitLen - 1)); ++i)
		W[i] = (LL)W[i - 1] * W[1] % mod;
	for(int i = (1 << (bitLen - 1)) - 1; i > 0; --i)
		w[i] = w[i << 1];
}
void NTT(int len, int x[], int flag) {
	register int i, j, k;
	for(i = 1, j = 0; i < len; ++i) {
		for(k = len >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			swap(x[i], x[j]);
	}
	register int *W = w + 1, t;
	for(i = 1; i < len; W += i, i <<= 1)
		for(j = 0; j < len; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = (LL)W[k] * x[i + j + k] % mod;
				x[i + j + k] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag == -1) {
		for(j = 0, k = 1; (1 << j) < len; ++j, k = (LL)k * inv2 % mod);
		reverse(x + 1, x + len);
		for(i = 0; i < len; ++i)
			x[i] = (LL)x[i] * k % mod;
	}
}
inline void polyFill(int n, int a[], int len, int A[]) {
	n = min(n, len);
	memcpy(A, a, n * sizeof(int));
	memset(A + n, 0, (len - n) * sizeof(int));
}
void polyInv(int n, int cur[], int nxt[]) {
	nxt[0] = 1;
	for(int len = 1; len < n; len <<= 1) {
		int upp = min(len + len, n);
		polyFill(len, nxt, len + len, B);
		NTT(len + len, B, 1);
		polyFill(upp, cur, len + len, A);
		NTT(len + len, A, 1);
		for(int i = 0; i < len + len; ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len + len, A, -1);
		polyFill(len, A + len, len + len, A);
		NTT(len + len, A, 1);
		for(int i = 0; i < len + len; ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len + len, A, -1);
		for(int i = len; i < upp; ++i)
			nxt[i] = A[i - len] ? mod - A[i - len] : 0;
	}
}
void polyMul(int aLen, int a[], int bLen, int b[], int cLen, int c[]) {
	int len;
	for(len = 1; len < aLen + bLen - 1; len <<= 1);
	polyFill(aLen, a, len, A);
	NTT(len, A, 1);
	if(aLen == bLen && a == b) {
		memcpy(B, A, len * sizeof(int));
	} else {
		polyFill(bLen, b, len, B);
		NTT(len, B, 1);
	}
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * B[i] % mod;
	NTT(len, A, -1);
	polyFill(len, A, cLen, c);
}
int deg, len, p[maxn], q[maxn];
void polyMerge(int aLen, int a[], int bLen, int b[], int &cLen, int c[]) {
	int tLen = aLen + bLen - 1;
	static int tmp[maxn << 1 | 1];
	polyMul(aLen, a, bLen, b, tLen, tmp);
	if(tLen <= deg) {
		cLen = tLen;
		memcpy(c, tmp, cLen * sizeof(int));
		return;
	}
	int dLen = tLen - deg;
	static int d[maxn];
	reverse(tmp, tmp + tLen);
	polyMul(dLen, tmp, dLen, q, dLen, d);
	reverse(tmp, tmp + tLen);
	reverse(d, d + dLen);
	polyFill(deg + 1, p, len, A);
	if(deg == len)
		mod_inc(A[0], p[deg]);
	NTT(len, A, 1);
	polyFill(dLen, d, len, B);
	NTT(len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * B[i] % mod;
	NTT(len, A, -1);
	for(int i = 0, j = len; i < deg; ++i, ++j) {
		mod_inc(tmp[i], mod - A[i]);
		if(j < tLen)
			mod_inc(tmp[i], tmp[j]);
	}
	memcpy(c, tmp, deg * sizeof(int));
	for(cLen = deg; cLen && !c[cLen - 1]; --cLen);
}
int n, pw[maxn], ivs, lenF, f[maxn], lenG, g[maxn];
int solve(int m) {
	memset(f, 0, (m + 1) * sizeof(int));
	memset(g, 0, (m + 1) * sizeof(int));
	lenF = f[0] = g[0] = 1;
	for(int i = m; i >= 1; --i) {
		int upp = m / i + 1, len;
		for(int j = 0; j < lenF; ++j)
			g[j + 1] = (LL)pw[i] * (mod - f[j]) % mod;
		polyInv(upp, g, q);
		for(len = 1; len + 1 < lenF + upp; len <<= 1);
		polyFill(lenF, f, len, A);
		NTT(len, A, 1);
		polyFill(upp, q, len, B);
		NTT(len, B, 1);
		for(int j = 0; j < len; ++j)
			A[j] = (LL)A[j] * B[j] % mod;
		NTT(len, A, -1);
		lenF = upp;
		memcpy(f, A, lenF * sizeof(int));
	}
	deg = lenG = lenF;
	for(int i = 0, j = deg - 1; i < deg; ++i, --j) {
		g[i] = (LL)pw[0] * f[j] % mod;
		p[i] = g[i] ? mod - g[i] : 0;
	}
	p[deg] = 1;
	reverse(p, p + deg + 1);
	polyInv(deg - 1, p, q);
	reverse(p, p + deg + 1);
	for(len = 1; len < deg; len <<= 1);
	lenF = n % deg + 1;
	memset(f, 0, lenF * sizeof(int));
	f[lenF - 1] = 1;
	for(int k = n / deg + 1; k > 0; k >>= 1) {
		if(k & 1)
			polyMerge(lenF, f, lenG, g, lenF, f);
		if(k > 1)
			polyMerge(lenG, g, lenG, g, lenG, g);
	}
	return lenF < deg ? 0 : (LL)f[deg - 1] * ivs % mod;
}
int mod_inv(int x) {
	int y = mod, u = 1, v = 0;
	while(x > 0) {
		int q = y / x, t = y % x;
		y = x;
		x = t;
		t = v - q * u;
		v = u;
		u = t;
	}
	return v < 0 ? v + mod : v;
}
int main() {
	int m, x, y;
	scanf("%d%d%d%d", &n, &m, &x, &y);
	initNTT(m << 1 | 1);
	x = (LL)x * mod_inv(y) % mod;
	pw[0] = mod + 1 - x;
	for(int i = 1; i <= m; ++i)
		pw[i] = (LL)pw[i - 1] * x % mod;
	ivs = mod_inv(pw[0]);
	printf("%d\n", mod_add(solve(m), mod - solve(m - 1)));
	return 0;
}
