#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 3003, maxm = 5001, maxl = 103, mod = 998244353;
const int maxLen = 13, maxs = 1 << maxLen | 1, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxs << 1 | 1], A[maxs], B[maxs];
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
	int *W = w + (1 << bitLen);
	W[0] = W[1] = 1;
	for(int i = (mod - 1) >> bitLen, x = gen; i > 0; i >>= 1, x = (LL)x * x % mod)
		if(i & 1)
			W[1] = (LL)W[1] * x % mod;
	for(int i = 2; i < (1 << bitLen); ++i)
		W[i] = (LL)W[i - 1] * W[1] % mod;
	for(int i = (1 << bitLen) - 1; i > 0; --i)
		w[i] = w[i << 1];
}
void NTT(int len, int x[], int flag) {
	register int i, j, k;
	for(i = 1, j = 0; i < len; ++i) {
		for(k = len >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			std::swap(x[i], x[j]);
	}
	register int *W = w + 1, t;
	for(i = 1; i < len; i <<= 1)
		for(j = 0, W += i; j < len; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = (LL)W[k] * x[i + j + k] % mod;
				x[i + j + k] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag == -1) {
		for(j = 0, k = 1; (1 << j) < len; ++j, k = (LL)k * inv2 % mod);
		std::reverse(x + 1, x + len);
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
void guessPoly(int n, int a[], int &deg, int poly[]) {
	static int lenF, f[maxn], posG, lenG, g[maxn], lenH, h[maxn];
	posG = -1;
	lenF = g[0] = 0;
	lenG = 1;
	for(int i = 0; i < n; ++i) {
		int diff = a[i];
		for(int j = 0, k = i - 1; j < lenF; ++j, --k)
			diff = (diff - (LL)f[j] * a[k]) % mod;
		if(!diff)
			continue;
		if(diff < 0)
			diff += mod;
		if(lenF + 1 <= i - posG + lenG) {
			lenH = lenF + 1;
			h[0] = mod_inv(diff);
			for(int j = 0; j < lenF; ++j)
				h[j + 1] = f[j] ? (LL)(mod - f[j]) * h[0] % mod : 0;
		} else {
			lenH = 0;
		}
		for(int tmp = i - 1 - posG + lenG; lenF < tmp; f[lenF++] = 0);
		for(int j = 0, k = i - 1 - posG; j < lenG; ++j, ++k)
			f[k] = (f[k] + (LL)diff * g[j]) % mod;
		if(lenH > 0) {
			posG = i;
			lenG = lenH;
			memcpy(g, h, lenG * sizeof(int));
		}
	}
	deg = lenF;
	poly[lenF] = 1;
	for(int i = 0, j = lenF - 1; j >= 0; ++i, --j)
		poly[j] = f[i] ? mod - f[i] : 0;
}
int n, m, a[maxn << 1 | 1], e[maxm << 1 | 1];
char buf[maxl];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m + m; ++i)
		scanf("%d", e + i);
	scanf("%s", buf);
	int bLen = strlen(buf), upp = (n + 1) << 1, lim = -1;
	for( ; bLen && !buf[bLen - 1]; --bLen);
	if(bLen < maxLen && (1 << (bLen - 1)) <= upp) {
		lim = 0;
		for(int i = bLen - 1; i >= 0; --i)
			lim = lim << 1 | (buf[i] == '1');
		upp = min(upp, lim + 1);
	}
	static int o = 0, ways[2][maxn] = {};
	a[0] = ways[o][0] = 1;
	for(int i = 1; i < upp; ++i) {
		o = !o;
		memcpy(ways[o], ways[!o], n * sizeof(int));
		for(int j = 0; j < m; ++j) {
			int u = e[j << 1] - 1, v = e[j << 1 | 1] - 1;
			mod_inc(ways[o][u], ways[!o][v]);
			mod_inc(ways[o][v], ways[!o][u]);
		}
		a[i] = a[i - 1];
		for(int j = 0; j < n; ++j)
			mod_inc(a[i], ways[o][j]);
	}
	if(upp == lim + 1) {
		printf("%d\n", a[lim]);
		return 0;
	}
	guessPoly(upp, a, deg, p);
	initNTT((deg - 1) << 1 | 1);
	reverse(p, p + deg + 1);
	polyInv(deg - 1, p, q);
	reverse(p, p + deg + 1);
	for(len = 1; len < deg; len <<= 1);
	static int lenF, f[maxn], lenG, g[maxn];
	g[0] = 0;
	lenF = f[0] = g[1] = 1;
	lenG = 2;
	for(int i = 0; i < bLen; ++i) {
		if(buf[i] == '1')
			polyMerge(lenF, f, lenG, g, lenF, f);
		if(i + 1 < bLen)
			polyMerge(lenG, g, lenG, g, lenG, g);
	}
	int ans = 0;
	for(int i = 0; i < lenF; ++i)
		ans = (ans + (LL)f[i] * a[i]) % mod;
	printf("%d\n", ans);
	return 0;
}
