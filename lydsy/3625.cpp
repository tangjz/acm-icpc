#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxLen = 17, maxs = 1 << maxLen | 1, mod = 998244353, gen = 3, inv2 = (mod + 1) >> 1;
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
			swap(x[i], x[j]);
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
		reverse(x + 1, x + len);
		for(i = 0; i < len; ++i)
			x[i] = (LL)x[i] * k % mod;
	}
}
void polyInv(int len, int cur[], int nxt[]) {
	static int tmp[maxs], dft[maxs];
	nxt[0] = 1;
	for(int n = 1; n < len; n <<= 1) {
		int upp = min(n + n, len);
		memcpy(dft, nxt, n * sizeof(int));
		memset(dft + n, 0, n * sizeof(int));
		NTT(n + n, dft, 1);
		memcpy(tmp, cur, upp * sizeof(int));
		memset(tmp + upp, 0, (n + n - upp) * sizeof(int));
		NTT(n + n, tmp, 1);
		for(int i = 0; i < n + n; ++i)
			tmp[i] = (LL)tmp[i] * dft[i] % mod;
		NTT(n + n, tmp, -1);
		memcpy(tmp, tmp + n, n * sizeof(int));
		memset(tmp + n, 0, n * sizeof(int));
		NTT(n + n, tmp, 1);
		for(int i = 0; i < n + n; ++i)
			tmp[i] = (LL)tmp[i] * dft[i] % mod;
		NTT(n + n, tmp, -1);
		for(int i = n; i < upp; ++i)
			nxt[i] = tmp[i - n] ? mod - tmp[i - n] : 0;
	}
}
void polySqrt(int len, int cur[], int nxt[]) {
	static int ivs[maxs], tmp[maxs], dft[maxs], dft2[maxs];
	nxt[0] = ivs[0] = dft[0] = 1;
	NTT(1, dft, 1);
	for(int n = 1; n < len; n <<= 1) {
		int upp = min(n + n, len);
		for(int i = 0; i < n; ++i)
			dft[i] = (LL)dft[i] * dft[i] % mod;
		NTT(n, dft, -1);
		for(int i = 0; i < n; ++i)
			if((dft[i] = (dft[i] - cur[i] - (LL)(n + i < upp ? cur[n + i] : 0)) * inv2 % mod) < 0)
				dft[i] += mod;
		memset(dft + n, 0, n * sizeof(int));
		NTT(n + n, dft, 1);
		memcpy(dft2, ivs, n * sizeof(int));
		memset(dft2 + n, 0, n * sizeof(int));
		NTT(n + n, dft2, 1);
		for(int i = 0; i < n + n; ++i)
			dft[i] = (LL)dft[i] * dft2[i] % mod;
		NTT(n + n, dft, -1);
		for(int i = n; i < upp; ++i)
			nxt[i] = dft[i - n] ? mod - dft[i - n] : 0;
		if(n + n < len) {
			memcpy(dft, nxt, (n + n) * sizeof(int));
			NTT(n + n, dft, 1);
			for(int i = 0; i < n + n; ++i)
				tmp[i] = (LL)dft[i] * dft2[i] % mod;
			NTT(n + n, tmp, -1);
			memcpy(tmp, tmp + n, n * sizeof(int));
			memset(tmp + n, 0, n * sizeof(int));
			NTT(n + n, tmp, 1);
			for(int i = 0; i < n + n; ++i)
				tmp[i] = (LL)tmp[i] * dft2[i] % mod;
			NTT(n + n, tmp, -1);
			for(int i = n; i < n + n; ++i)
				ivs[i] = tmp[i - n] ? mod - tmp[i - n] : 0;
		}
	}
}
int n, m, f[maxs], g[maxs];
int main() {
	scanf("%d%d", &n, &m);
	initNTT(m + 1);
	while(n--) {
		int x;
		scanf("%d", &x);
		++f[x];
	}
	f[0] = 1;
	for(int i = 1; i <= m; ++i)
		f[i] = 4LL * (mod - f[i]) % mod;
	polySqrt(m + 1, f, g);
	for(int i = 1; i <= m; ++i)
		g[i] = (LL)g[i] * inv2 % mod;
	polyInv(m + 1, g, f);
	for(int i = 1; i <= m; ++i)
		printf("%d\n", f[i]);
	return 0;
}