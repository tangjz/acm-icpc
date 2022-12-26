#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
typedef std::complex<DB> Complex;
const int maxn = 100001, maxm = 1 << 17 | 1, mod = (int)1e9 + 33, sp = 15, msk = (1 << sp) - 1;
const DB pi = acos(-1.0);
Complex w[maxm], A[maxm], B[maxm], C[maxm], D[maxm];
int t, n, inv[maxn], f[maxn], g[maxn];
int maxLen, a[maxm], b[maxm];
void FFT(int n, Complex a[], int flag) {
	static int bitLen = 0, bitRev[maxm] = {};
	if(n != (1 << bitLen)) {
		for(bitLen = 0; 1 << bitLen < n; ++bitLen);
		for(int i = 1; i < n; ++i)
			bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
	}
	for(int i = 0; i < n; ++i)
		if(i < bitRev[i])
			std::swap(a[i], a[bitRev[i]]);
	for(int i = 1, d = 1; d < n; ++i, d <<= 1)
		for(int j = 0; j < n; j += d << 1)
			for(int k = 0; k < d; ++k) {
				Complex &AL = a[j + k], &AH = a[j + k + d], TP = w[k << (maxLen - i)] * AH;
				AH = AL - TP;
				AL = AL + TP;
			}
	if(flag != -1)
		return;
	std::reverse(a + 1, a + n);
	Complex tr((DB)1 / n, 0);
	for(int i = 0; i < n; ++i)
		a[i] *= tr;
}
void conv(int len, int a[], int b[]) { // a := a * b
	for(int i = 0; i < len; ++i) {
		A[i] = Complex(a[i] & msk, a[i] >> sp);
		B[i] = Complex(b[i] & msk, b[i] >> sp);
	}
	FFT(len, A, 1);
	FFT(len, B, 1);
	Complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
	for(int i = 0; i < len; ++i) {
		int j = (len - i) & (len - 1);
		Complex AL = (A[i] + std::conj(A[j])) * trL;
		Complex AH = (A[i] - std::conj(A[j])) * trH;
		Complex BL = (B[i] + std::conj(B[j])) * trL;
		Complex BH = (B[i] - std::conj(B[j])) * trH;
		C[i] = AL * (BL + BH * tr);
		D[i] = AH * (BL + BH * tr);
	}
	FFT(len, C, -1);
	FFT(len, D, -1);
	for(int i = 0; i < len; ++i) {
		int v11 = (LL)(C[i].real() + 0.5) % mod, v12 = (LL)(C[i].imag() + 0.5) % mod;
		int v21 = (LL)(D[i].real() + 0.5) % mod, v22 = (LL)(D[i].imag() + 0.5) % mod;
		a[i] = (((((LL)v22 << sp) + v12 + v21) << sp) + v11) % mod;
	}
}
inline void fill(int aLen, int a[], int bLen, int b[]) { // assert(bLen <= aLen);
	memcpy(a, b, bLen * sizeof(int));
	memset(a + bLen, 0, (aLen - bLen) * sizeof(int));
}
void solve(int L, int R) {
	if(L == R) {
		g[L] = L ? (LL)g[L] * inv[L] % mod : 1;
		return;
	}
	int M = (L + R) >> 1;
	solve(L, M);
	int len;
	for(len = 1; len < R - L; len <<= 1);
	fill(len, a, M - L + 1, g + L);
	fill(len, b, R - L, f);
	conv(len, a, b);
	for(int i = M + 1, *_a = a - L - 1; i <= R; ++i)
		if((g[i] += _a[i]) >= mod)
			g[i] -= mod;
	solve(M + 1, R);
}
int main() {
	int k;
	scanf("%d%d", &n, &k);
	inv[1] = f[0] = 1;
	for(int i = 2; i <= n; ++i) {
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		f[i - 1] = 1;
	}
	while(k--) {
		int x;
		scanf("%d", &x);
		f[x - 1] = 0;
	}
	for(maxLen = 1; 1 << maxLen <= n; ++maxLen);
	for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i) {
		int j = i, k = ilim >> 1; // 2 pi / ilim
		for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
		w[i] = std::complex<DB>(cos(pi / k * j), sin(pi / k * j));
	}
	solve(0, n);
	for(int i = 2; i <= n; ++i)
		g[n] = (LL)g[n] * i % mod;
	printf("%d\n", g[n]);
	return 0;
}
