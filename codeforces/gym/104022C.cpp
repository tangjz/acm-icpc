#include <bits/stdc++.h>
typedef long long LL;
const int maxLen = 17, maxs = 1 << maxLen | 1, mod = 998244353, gen = 3;
int inv[maxs | 1], w[maxs << 1 | 1];
inline int modAdd(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
}
inline int modSub(int x, int y) {
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
	for(int i = 2; i <= (1 << bitLen); ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
}
void NTT(int len, int x[], int flag) {
	int i, j, k;
	for(i = 1, j = 0; i < len; ++i) {
		for(k = len >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			std::swap(x[i], x[j]);
	}
	int *W = w + 1, t;
	for(i = 1; i < len; i <<= 1)
		for(j = 0, W += i; j < len; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = (LL)W[k] * x[i + j + k] % mod;
				x[i + j + k] = modSub(x[j + k], t);
				x[j + k] = modAdd(x[j + k], t);
			}
	if(flag == -1) {
		std::reverse(x + 1, x + len);
		for(i = 0, k = inv[len]; i < len; ++i)
			x[i] = (LL)x[i] * k % mod;
	}
}
void polyExp(int n, int cur[], int nxt[]) {
	assert(!cur[0]);
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
		B[0] = modSub(B[0], 1);
		for(int i = 1; i < len; ++i)
			A[i - 1] = (LL)g[i] * i % mod;
		A[len - 1] = 0;
		NTT(len, A, 1);
		for(int i = 0; i < len; ++i)
			A[i] = (LL)A[i] * C[i] % mod;
		NTT(len, A, -1);
		for(int i = len - 3; i >= 0; --i)
			A[i + 1] = modSub(A[i], f[i]);
		A[0] = A[len - 1];
		A[len - 1] = 0;
		for(int i = 0, j = len - 1; i < len && j + 1 < n; ++i, ++j)
			A[i] = modSub(A[i], f[j]);
		memset(B + len, 0, len * sizeof(int));
		NTT(len << 1, B, 1);
		memcpy(C, f, (len - 1) * sizeof(int));
		memset(C + len - 1, 0, (len + 1) * sizeof(int));
		NTT(len << 1, C, 1);
		for(int i = 0; i < (len << 1); ++i)
			B[i] = (LL)B[i] * C[i] % mod;
		NTT(len << 1, B, -1);
		for(int i = 0; i < len; ++i)
			A[i] = (LL)(i ? modSub(A[i], B[i - 1]) : A[i]) * inv[len + i] % mod;
		memset(A + len, 0, len * sizeof(int));
		NTT(len << 1, A, 1);
		memcpy(B, g, len * sizeof(int));
		memset(B + len, 0, len * sizeof(int));
		NTT(len << 1, B, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len << 1, A, -1);
		for(int i = 0; i < len; ++i)
			g[len + i] = modSub(0, A[i]);
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
			h[len + i] = modSub(0, A[i]);
	}
	memcpy(nxt, g, n * sizeof(int));
}
void solve(int sta, int len, int f[], int g[], int h[]) {
	if(len == 1) {
		h[sta] = f[sta];
		return;
	}
	static int AA[maxs], BB[maxs << 1 | 1];
	const int half = len >> 1;
	int *F = f + sta, *G = g + sta;
	int *A = AA + sta, *B = BB + sta + sta;
	solve(sta, half, f, g, h);

	memcpy(A, F, len * sizeof(int));
	NTT(len, A, 1);
	memcpy(B, G, half * sizeof(int));
	memset(B + half, 0, half * sizeof(int));
	NTT(len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * B[i] % mod;
	NTT(len, A, -1);
	for(int i = half; i < len; ++i) {
		int val = F[i];
		F[i] = modAdd(val, A[i - 1]);
		A[i - half] = val;
	}
	// DO NOT modify AA[sta..sta+half-1], BB[sta+sta...sta+sta+len-1] inside
	solve(sta + half, half, f, g, h);
	memcpy(F + half, A, half * sizeof(int));

	memcpy(A, G + half, half * sizeof(int));
	memset(A + half, 0, half * sizeof(int));
	NTT(len, A, 1);
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * B[i] % mod;
	NTT(len, A, -1);
	for(int i = 0; i < half; ++i) {
		G[i] = modAdd(G[i], G[half + i]);
		G[half + i] = 0;
	}
	for(int i = 1; i < len; ++i)
		G[i] = modAdd(G[i], A[i - 1]);
}
int main() {
	int T, len = 1;
	scanf("%d", &T);
	std::vector<int> queries;
	queries.reserve(T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		scanf("%d", &n);
		queries.push_back(n);
		for( ; len <= n; len <<= 1);
	}

	static int f[maxs], g[maxs], h[maxs];
	initNTT(len);
	f[0] = 0;
	f[1] = 1;
	for(int i = 2; i < len; ++i)
		f[i] = (LL)f[i - 1] * inv[i] % mod;
	polyExp(len, f, f);
	for(int i = 2, prd = 1; i < len; ++i) {
		prd = (LL)prd * i % mod;
		f[i] = (LL)f[i] * prd % mod;
	}

	for(int i = 1, j = 0; i <= len; ++i) {
		for( ; (LL)j * j < (LL)i * (i + j); ++j);
		g[i - 1] = j - i;
	}
	solve(0, len, f, g, h);

	for(int n: queries)
		printf("%d\n", h[n]);
	return 0;
}