#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB pi = acos(-1.0);
const int maxm = (int)1e4 + 1, maxLen = 15, maxs = 1 << maxLen | 1, mod = 19;
struct Complex {
	DB r, i;
	Complex() { r = i = 0; }
	Complex(DB r, DB i) : r(r), i(i) {}
	Complex operator + (Complex const &t) const { return Complex(r + t.r, i + t.i); }
	Complex operator - (Complex const &t) const { return Complex(r - t.r, i - t.i); }
	Complex operator * (Complex const &t) const { return Complex(r * t.r - i * t.i, r * t.i + i * t.r); }
} w[maxs << 1 | 1];
void initFFT(int len) {
	int bitLen;
	for(bitLen = 0; (1 << bitLen) < len; ++bitLen);
	Complex *W = w + (1 << bitLen);
	for(int i = 0, ilim = 1 << bitLen; i < ilim; ++i) {
		int j = i << 1, k = ilim; // 2 pi / ilim
		for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
		W[i] = Complex(cos(pi / k * j), sin(pi / k * j));
	}
	for(int i = (1 << bitLen) - 1; i > 0; --i)
		w[i] = w[i << 1];
}
void FFT(int len, Complex x[], int flag) {
	register int i, j, k;
	for(i = 1, j = 0; i < len; ++i) {
		for(k = len >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			std::swap(x[i], x[j]);
	}
	Complex *W = w + 1, t;
	for(i = 1; i < len; i <<= 1)
		for(j = 0, W += i; j < len; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = W[k] * x[i + j + k];
				x[i + j + k] = x[j + k] - t;
				x[j + k] = x[j + k] + t;
			}
	if(flag == -1) {
		std::reverse(x + 1, x + len);
		for(i = 0; i < len; ++i)
			x[i].r /= len;
	}
}
long long n;
int m, pL, pR, f[maxm], g[maxm], h[maxm];
Complex A[maxs], B[maxs];
void DFT(int n, int a[], int len, Complex A[], int flag) {
	if(flag == 1) {
		for(int i = 0; i < len; ++i)
			A[i] = i < n ? Complex(a[i], 0) : Complex();
		FFT(len, A, 1);
	} else {
		FFT(len, A, -1);
		for(int i = 0; i < n; ++i)
			a[i] = (int)(A[i].r + 0.5) % mod;
	}
}
int main() {
	scanf("%lld%d%d", &n, &m, &pR);
	--n;
	for(int i = 0; i < m; ++i)
		scanf("%d", f + i);
	if(!n) {
		for(int i = 0; i < m; ++i)
			printf("%d%c", f[i], " \n"[i == m - 1]);
		return 0;
	}
	for(int i = 0; i < pR; ++i)
		scanf("%d", g + i);
	for( ; pL < pR && !g[pL]; ++pL);
	if(pL == pR || pL && (m <= n || m <= n * pL)) {
		for(int i = 0; i < m; ++i)
			printf("%d%c", 0, " \n"[i == m - 1]);
		return 0;
	}
	int sft = n * pL, upp = m - sft, len;
	for(len = 1; len + 1 < upp + upp; len <<= 1);
	initFFT(len);
	int prd = 1, ivs = 1;
	for(int k = n % (mod - 1), x = g[pL]; k > 0; k >>= 1, x = x * x % mod)
		if(k & 1)
			prd = prd * x % mod;
	for(int x = g[pL]; x != 1; ++ivs, (x += g[pL]) >= mod && (x -= mod));
	for(int i = pL; i < pR; ++i)
		g[i - pL] = g[i] * ivs % mod;
	for(int i = pR - pL; i < upp; ++i)
		g[i] = 0;
	memset(h, 0, upp * sizeof(int));
	h[0] = 1;
	int ex = 0, pw = 1;
	for( ; pw < upp; ++ex, pw *= mod);
	while(ex > 0) {
		--ex;
		pw /= mod;
		int upp2 = (upp - 1) / pw + 1, len2;
		for(len2 = 1; len2 + 1 < upp2 + upp2; len2 <<= 1);
		static int a[maxm];
		memcpy(a, g, upp2 * sizeof(int));
		DFT(upp2, a, len2, A, 1);
		for(int k = n / pw % mod; k > 0; k >>= 1) {
			if(k & 1) {
				DFT(upp2, h, len2, B, 1);
				for(int i = 0; i < len2; ++i)
					B[i] = A[i] * B[i];
				DFT(upp2, h, len2, B, -1);
			}
			if(k > 1) {
				for(int i = 0; i < len2; ++i)
					A[i] = A[i] * A[i];
				DFT(upp2, a, len2, A, -1);
				DFT(upp2, a, len2, A, 1);
			}
		}
		if(ex > 0)
			for(int i = upp2 - 1, j = i * mod; i > 0; --i, j -= mod) {
				h[j] = h[i];
				h[i] = 0;
			}
	}
	for(int i = 0; i < upp; ++i)
		h[i] = h[i] * prd % mod;
	DFT(upp, f, len, A, 1);
	DFT(upp, h, len, B, 1);
	for(int i = 0; i < len; ++i)
		B[i] = A[i] * B[i];
	DFT(upp, h, len, B, -1);
	for(int i = 0; i < m; ++i)
		printf("%d%c", i < sft ? 0 : h[i - sft], " \n"[i == m - 1]);
	return 0;
}
