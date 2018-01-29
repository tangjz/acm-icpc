#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e7 + 1, maxm = (int)4e6 + 1, maxLen = 19, maxs = 1 << maxLen | 1, mod = (int)1e9 + 7;
const double pi = acos(-1.0);
struct Complex {
	double r, i;
	Complex() {}
	Complex(double r, double i) : r(r), i(i) {}
	Complex operator + (Complex const &t) const { return Complex(r + t.r, i + t.i); }
	Complex operator - (Complex const &t) const { return Complex(r - t.r, i - t.i); }
	Complex operator * (Complex const &t) const { return Complex(r * t.r - i * t.i, r * t.i + i * t.r); }
	Complex conj() const { return Complex(r, -i); }
} w[maxs];
int msk, sp;
void FFT_init() {
	for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i) {
		int j = i, k = ilim >> 1;
		for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
		w[i] = Complex(cos(pi / k * j), sin(pi / k * j));
	}
	for(sp = 1; 1 << (sp << 1) < mod; ++sp);
	msk = (1 << sp) - 1;
}
void FFT(int n, Complex a[], int flag) {
	static int bitLen = 0, bitRev[maxs];
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
	for(int i = 0; i < n; ++i) {
		 a[i].r /= n;
		 a[i].i /= n;
	}
}
void conv(int aLen, int a[], int bLen, int b[], int cLen, int c[]) {
	int len;
	static Complex A[maxs], B[maxs], C[maxs], D[maxs];
	for(len = 1; len < aLen + bLen - 1; len <<= 1);
	for(int i = 0; i < len; ++i) {
		A[i] = i < aLen ? Complex(a[i] & msk, a[i] >> sp) : Complex(0, 0);
		B[i] = i < bLen ? Complex(b[i] & msk, b[i] >> sp) : Complex(0, 0);
	}
	FFT(len, A, 1);
	FFT(len, B, 1);
	Complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
	for(int i = 0; i < len; ++i) {
		int j = (len - i) & (len - 1);
		Complex AL = (A[i] + A[j].conj()) * trL;
		Complex AH = (A[i] - A[j].conj()) * trH;
		Complex BL = (B[i] + B[j].conj()) * trL;
		Complex BH = (B[i] - B[j].conj()) * trH;
		C[i] = AL * (BL + BH * tr);
		D[i] = AH * (BL + BH * tr);
	}
	FFT(len, C, -1);
	FFT(len, D, -1);
	for(int i = 0; i < cLen; ++i) {
		int v11 = (LL)(C[i].r + 0.5) % mod, v12 = (LL)(C[i].i + 0.5) % mod;
		int v21 = (LL)(D[i].r + 0.5) % mod, v22 = (LL)(D[i].i + 0.5) % mod;
		c[i] = (((((LL)v22 << sp) + v12 + v21) << sp) + v11) % mod;
	}
}
void polyMul(int len, int a[], int b[], int c[]) {
	static int tp[maxm], rt[maxm];
	for(int i = 0; i < len; ++i)
		rt[i] = 0;
	for(int i = 0; i < len; i += 1 << (maxLen - 1))
		for(int j = 0; i + j < len; j += 1 << (maxLen - 1)) {
			conv(min(i + (1 << (maxLen - 1)), len) - i, a + i, min(j + (1 << (maxLen - 1)), len) - j, b + j, min(i + j + (1 << maxLen) - 1, len) - i - j, tp);
			for(int k = 0; k < (1 << maxLen) - 1 && i + j + k < len; ++k)
				(rt[i + j + k] += tp[k]) >= mod && (rt[i + j + k] -= mod);
		}
	for(int i = 0; i < len; ++i)
		c[i] = rt[i];
}
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int n, m, fact[maxn], iact[maxn], f[maxm], g[maxm];
int main() {
	FFT_init();
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 0; i <= m; ++i) {
			f[i] = iact[i];
			g[i] = (LL)f[i] * mod_pow(i, n) % mod;
			if((i & 1) && f[i])
				f[i] = mod - f[i];
		}
		polyMul(m + 1, f, g, f);
		int ans = 0;
		for(int i = 0; i <= m; ++i)
			if((m - i) & 1)
				ans = (ans - (LL)fact[n - i] * iact[m - i] % mod * fact[i] % mod * f[i]) % mod;
			else
				ans = (ans + (LL)fact[n - i] * iact[m - i] % mod * fact[i] % mod * f[i]) % mod;
		(ans = (LL)ans * iact[n - m] % mod) < 0 && (ans += mod);
		printf("%d\n", ans);
	}
	return 0;
}
