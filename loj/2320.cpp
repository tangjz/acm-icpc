#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e4 + 1, mod = 998244353, maxLen = 16, maxs = 1 << maxLen | 1, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxs], inv[maxs], A[maxs], B[maxs], C[maxs];
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
}
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? (x + mod) : x;
}
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
void initNTT(int len) {
	int bitLen;
	for(bitLen = 0; (1 << bitLen) < len; ++bitLen);
	int *W = w + (1 << (bitLen - 1));
	W[0] = 1;
	W[1] = mod_pow(gen, (mod - 1) >> bitLen);
	for(int i = 2; i < (1 << (bitLen - 1)); ++i)
		W[i] = (LL)W[i - 1] * W[1] % mod;
	for(int i = (1 << (bitLen - 1)) - 1; i > 0; --i)
		w[i] = w[i << 1];
	inv[1] = 1;
	for(int i = 2; i < (1 << bitLen); ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
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
void polyInv(int n, int cur[], int nxt[]) { // cur != nxt
	nxt[0] = 1;
	for(int len = 1; len < n; len <<= 1) {
		int upp = min(len << 1, n);
		polyFill(len, nxt, len << 1, B);
		NTT(len << 1, B, 1);
		polyFill(upp, cur, len << 1, A);
		NTT(len << 1, A, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len << 1, A, -1);
		polyFill(len, A + len, len << 1, A);
		NTT(len << 1, A, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len << 1, A, -1);
		for(int i = len; i < upp; ++i)
			nxt[i] = A[i - len] ? mod - A[i - len] : 0;
	}
}
void polyExp(int n, int cur[], int nxt[]) {
	static int f[maxs], g[maxs], h[maxs];
	for(int i = 1; i < n; ++i)
		f[i - 1] = (LL)cur[i] * i % mod;
	f[n - 1] = 0;
	g[0] = h[0] = B[0] = 1;
	NTT(1, B, 1);
	for(int len = 1; len < n; len <<= 1) {
		memcpy(C, h, len * sizeof(int));
		NTT(len, C, 1);
		for(int i = 0; i < len; ++i)
			B[i] = (LL)B[i] * C[i] % mod;
		NTT(len, B, -1);
		B[0] = mod_sub(B[0], 1);
		for(int i = 1; i < len; ++i)
			A[i - 1] = (LL)g[i] * i % mod;
		A[len - 1] = 0;
		NTT(len, A, 1);
		for(int i = 0; i < len; ++i)
			A[i] = (LL)A[i] * C[i] % mod;
		NTT(len, A, -1);
		for(int i = len - 3; i >= 0; --i)
			A[i + 1] = mod_sub(A[i], f[i]);
		A[0] = A[len - 1];
		A[len - 1] = 0;
		for(int i = 0, j = len - 1; i < len && j + 1 < n; ++i, ++j)
			A[i] = mod_sub(A[i], f[j]);
		memset(B + len, 0, len * sizeof(int));
		NTT(len << 1, B, 1);
		polyFill(len - 1, f, len << 1, C);
		NTT(len << 1, C, 1);
		for(int i = 0; i < (len << 1); ++i)
			B[i] = (LL)B[i] * C[i] % mod;
		NTT(len << 1, B, -1);
		for(int i = 0; i < len; ++i)
			A[i] = (LL)mod_sub(A[i], i ? B[i - 1] : 0) * inv[len + i] % mod;
		memset(A + len, 0, len * sizeof(int));
		NTT(len << 1, A, 1);
		polyFill(len, g, len << 1, B);
		NTT(len << 1, B, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len << 1, A, -1);
		for(int i = 0; i < len; ++i)
			g[len + i] = mod_sub(0, A[i]);
		if((len << 1) >= n)
			break;
		memcpy(B, g, (len << 1) * sizeof(int));
		NTT(len << 1, B, 1);
		polyFill(len, h, len << 1, C);
		NTT(len << 1, C, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)B[i] * C[i] % mod;
		NTT(len << 1, A, -1);
		polyFill(len, A + len, len << 1, A);
		NTT(len << 1, A, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)A[i] * C[i] % mod;
		NTT(len << 1, A, -1);
		for(int i = 0; i < len; ++i)
			h[len + i] = mod_sub(0, A[i]);
	}
	memcpy(nxt, g, n * sizeof(int));
}
int n, m, sz[maxn], f[maxn << 1 | 1], g[maxn], h[maxn];
void solve(int L, int R) {
	if(L == R)
		return;
	int M = (L + R) >> 1;
	solve(L, M);
	solve(M + 1, R);
	int nxt = sz[L] + sz[M + 1] - 1, len;
	for(len = 1; len < nxt; len <<= 1);
	polyFill(sz[L], f + (L << 1), len, A);
	NTT(len, A, 1);
	polyFill(sz[M + 1], f + ((M + 1) << 1), len, B);
	NTT(len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * B[i] % mod;
	NTT(len, A, -1);
	polyFill(len, A, sz[L] = nxt, f + (L << 1));
}
int main() {
	scanf("%d%d", &n, &m);
	int mul = 1;
	for(int i = 0, x; i < n; ++i) {
		scanf("%d", &x);
		sz[i] = 2;
		f[i << 1] = 1;
		f[i << 1 | 1] = mod - x;
		mul = (LL)mul * x % mod;
	}
	int len;
	for(len = 1; len + 1 < ((n - 1) << 1); len <<= 1);
	initNTT(max(len, n - 1));
	solve(0, n - 1);
	polyInv(n - 1, f, C);
	memset(C + n - 1, 0, (len - n + 1) * sizeof(int));
	NTT(len, C, 1);
	for(int i = 0, ivs = 1; i < n - 1; ++i) {
		f[i] = (LL)(mod - f[i]) * i % mod;
		h[i] = mod_pow(i + 1, m);
		g[i] = (LL)h[i] * h[i] % mod * ivs % mod;
		h[i] = (LL)h[i] * ivs % mod;
		ivs = (LL)ivs * inv[i + 1] % mod;
	}
	polyFill(n - 1, f, len, A);
	NTT(len, A, 1);
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * C[i] % mod;
	NTT(len, A, -1);
	polyFill(len, A, n - 1, f);
	f[0] = n;
	polyInv(n - 1, h, C);
	memset(C + n - 1, 0, (len - n + 1) * sizeof(int));
	NTT(len, C, 1);
	polyFill(n - 1, g, len, A);
	NTT(len, A, 1);
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * C[i] % mod;
	NTT(len, A, -1);
	polyFill(len, A, n - 1, g);
	for(int i = 1; i < n - 1; ++i)
		h[i - 1] = (LL)h[i] * i % mod;
	h[n - 2] = 0;
	polyFill(n - 1, h, len, A);
	NTT(len, A, 1);
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * C[i] % mod;
	NTT(len, A, -1);
	polyFill(len, A, n - 1, h);
	for(int i = n - 2; i > 0; --i)
		h[i] = (LL)h[i - 1] * inv[i] % mod;
	h[0] = 0;
	for(int i = 0; i < n - 1; ++i) {
		g[i] = (LL)f[i] * g[i] % mod;
		h[i] = (LL)f[i] * h[i] % mod;
	}
	polyExp(n - 1, h, h);
	int ans = 0;
	for(int i = 0, j = n - 2; j >= 0; ++i, --j)
		ans = (ans + (LL)g[i] * h[j]) % mod;
	for(int i = 2; i <= n - 2; ++i)
		ans = (LL)ans * i % mod;
	ans = (LL)ans * mul % mod;
	printf("%d\n", ans);
	return 0;
}