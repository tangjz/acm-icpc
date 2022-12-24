#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxLen = 18, maxs = 1 << maxLen | 1, mod = 950009857, gen = 7, inv2 = (mod + 1) >> 1;
int inv[maxs], w[maxs << 1 | 1];
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
void polyInv(int n, int cur[], int nxt[]) {
	static int A[maxs], B[maxs];
	nxt[0] = 1;
	for(int len = 1; len < n; len <<= 1) {
		int upp = min(len + len, n);
		memcpy(B, nxt, len * sizeof(int));
		memset(B + len, 0, len * sizeof(int));
		NTT(len + len, B, 1);
		memcpy(A, cur, upp * sizeof(int));
		memset(A + upp, 0, (len + len - upp) * sizeof(int));
		NTT(len + len, A, 1);
		for(int i = 0; i < len + len; ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len + len, A, -1);
		memcpy(A, A + len, len * sizeof(int));
		memset(A + len, 0, len * sizeof(int));
		NTT(len + len, A, 1);
		for(int i = 0; i < len + len; ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len + len, A, -1);
		for(int i = len; i < upp; ++i)
			nxt[i] = A[i - len] ? mod - A[i - len] : 0;
	}
}
void polyLog(int n, int cur[], int nxt[]) {
	int len;
	static int A[maxs], B[maxs];
	for(len = 1; len + 1 < ((n - 1) << 1); len <<= 1);
	for(int i = 1; i < n; ++i)
		A[i - 1] = (LL)cur[i] * i % mod;
	memset(A + n - 1, 0, (len - n + 1) * sizeof(int));
	NTT(len, A, 1);
	polyInv(n - 1, cur, B);
	memset(B + n - 1, 0, (len - n + 1) * sizeof(int));
	NTT(len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * B[i] % mod;
	NTT(len, A, -1);
	nxt[0] = 0;
	for(int i = 1; i < n; ++i)
		nxt[i] = (LL)A[i - 1] * inv[i] % mod;
}
void polyExp(int n, int cur[], int nxt[]) {
	static int f[maxs], g[maxs], h[maxs], A[maxs], B[maxs], C[maxs];
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
		// assert(A[len - 2] == f[len - 2]);
		for(int i = len - 3; i >= 0; --i)
			A[i + 1] = mod_sub(A[i], f[i]);
		A[0] = A[len - 1];
		A[len - 1] = 0;
		for(int i = 0, j = len - 1; i < len && j + 1 < n; ++i, ++j)
			A[i] = mod_sub(A[i], f[j]);
		memset(B + len, 0, len * sizeof(int));
		NTT(len << 1, B, 1);
		memcpy(C, f, (len - 1) * sizeof(int));
		memset(C + len - 1, 0, (len + 1) * sizeof(int));
		NTT(len << 1, C, 1);
		for(int i = 0; i < (len << 1); ++i)
			B[i] = (LL)B[i] * C[i] % mod;
		NTT(len << 1, B, -1);
		for(int i = 0; i < len; ++i)
			A[i] = (LL)mod_sub(A[i], i ? B[i - 1] : 0) * inv[len + i] % mod;
		memset(A + len, 0, len * sizeof(int));
		NTT(len << 1, A, 1);
		memcpy(B, g, len * sizeof(int));
		memset(B + len, 0, len * sizeof(int));
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
		memcpy(C, h, len * sizeof(int));
		memset(C + len, 0, len * sizeof(int));
		NTT(len << 1, C, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)B[i] * C[i] % mod;
		NTT(len << 1, A, -1);
		memcpy(A, A + len, len * sizeof(int));
		memset(A + len, 0, len * sizeof(int));
		NTT(len << 1, A, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)A[i] * C[i] % mod;
		NTT(len << 1, A, -1);
		for(int i = 0; i < len; ++i)
			h[len + i] = mod_sub(0, A[i]);
	}
	memcpy(nxt, g, n * sizeof(int));
}
int n, m, f[maxn], g[maxn];
int main() {
	scanf("%d%d", &n, &m);
	initNTT(max(n, (n - 2) << 1 | 1));
	f[0] = 1;
	for(int i = 0, x; i < m; ++i) {
		scanf("%d", &x);
		f[x - 1] = mod - 1;
	}
	polyLog(n, f, g);
	for(int i = 1; i < n; ++i)
		g[i] = (LL)g[i] * (mod - n) % mod;
	polyExp(n, g, f);
	int res = (LL)f[n - 1] * (inv[n] ? inv[n] : mod - (int)(mod / n * (LL)inv[mod % n] % mod)) % mod;
	printf("%d\n", res);
	return 0;
}