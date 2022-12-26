#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = 998244353, maxLen = 18, maxs = 1 << maxLen | 1, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxs], A[maxs], B[maxs];
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
int n, m, f[maxn];
void solve(int L, int R) {
	if(L == R)
		return;
	int M = (L + R) >> 1;
	solve(L, M);
	solve(M + 1, R);
	int len;
	for(len = 1; len <= R - L + 1; len <<= 1);
	A[0] = B[0] = 1;
	polyFill(M - L + 1, f + L, len - 1, A + 1);
	NTT(len, A, 1);
	polyFill(R - M, f + M + 1, len - 1, B + 1);
	NTT(len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = (LL)A[i] * B[i] % mod;
	NTT(len, A, -1);
	polyFill(len - 1, A + 1, R - L + 1, f + L);
}
int main() {
	initNTT((maxn - 1) << 1);
	for(int Case = 1; scanf("%d%d", &n, &m) == 2 && !(!n && !m); ++Case) {
		for(int i = 1; i <= n; ++i)
			scanf("%d", f + i);
		int len;
		for(len = 1; len < n + m; len <<= 1);
		solve(1, n);
		f[0] = 1;
		polyFill(n + 1, f, len, A);
		NTT(len, A, 1);
		B[0] = 1;
		B[1] = 0;
		for(int i = 2; i < n + m; ++i)
			B[i] = (i - 1LL) * (B[i - 1] + B[i - 2]) % mod;
		memset(B + n + m, 0, (len - n - m) * sizeof(int));
		NTT(len, B, 1);
		for(int i = 0; i < len; ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len, A, -1);
		printf("Case #%d:\n", Case);
		for(int i = n; i < n + m; ++i)
			printf("%d\n", A[i]);
	}
	return 0;
}
