#include <cmath>
#include <stdio.h>
#include <algorithm>
typedef long long LL;
typedef double DB;
const int maxn = 1 << 17, maxLen = 19, maxm = 1 << maxLen | 1, mod = 1000000007;
const DB pi = acos(-1.0), maxv = 1e14;
int n, f[maxn | 1], g[maxn | 1], sp, msk;
struct complex {
	DB r, i;
	complex() {}
	complex(DB r, DB i) : r(r), i(i) {}
	complex operator + (complex const &t) const { return complex(r + t.r, i + t.i); }
	complex operator - (complex const &t) const { return complex(r - t.r, i - t.i); }
	complex operator * (complex const &t) const { return complex(r * t.r - i * t.i, r * t.i + i * t.r); }
	complex conj() const { return complex(r, -i); }
} w[maxm];
void FFT_init() {
	for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i) {
		int j = i, k = ilim >> 1;
		for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
		w[i] = complex(cos(pi / k * j), sin(pi / k * j));
	}
	for(sp = 1; 1 << (sp << 1) < mod; ++sp);
	msk = (1 << sp) - 1;
}
void FFT(int n, complex a[], int flag) {
	static int bitLen = 0, bitRev[maxm];
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
				complex &AL = a[j + k], &AH = a[j + k + d], TP = w[k << (maxLen - i)] * AH;
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
	static complex A[maxm], B[maxm], C[maxm], D[maxm];
	for(len = 1; len < aLen + bLen - 1; len <<= 1);
	for(int i = 0; i < len; ++i) {
		A[i] = i < aLen ? complex(a[i] & msk, a[i] >> sp) : complex(0, 0);
		B[i] = i < bLen ? complex(b[i] & msk, b[i] >> sp) : complex(0, 0);
	}
	FFT(len, A, 1);
	FFT(len, B, 1);
	complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
	for(int i = 0; i < len; ++i) {
		int j = (len - i) & (len - 1);
		complex AL = (A[i] + A[j].conj()) * trL;
		complex AH = (A[i] - A[j].conj()) * trH;
		complex BL = (B[i] + B[j].conj()) * trL;
		complex BH = (B[i] - B[j].conj()) * trH;
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
inline void polyInv(int n, int f[], int g[]) {
	if(n == 1) {
		g[0] = 1;
		return;
	}
	int half = (n + 1) >> 1;
	polyInv(half, f, g);
	static int h[maxm];
	conv(n, f, half, g, n, h);
	conv(half, g, n - half, h + half, n - half, g + half);
	for(int i = half; i < n; ++i)
		g[i] = g[i] ? mod - g[i] : 0;
}
int main() {
	n = 100001;
	static int inv[maxn | 1];
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	f[0] = 1;
	for(int i = 1; i < n; ++i)
		f[i] = (LL)f[i - 1] * inv[i + 1] % mod;
	FFT_init();
	polyInv(n, f, g);
	for(int i = 0, pw = 1, fct = 1; i < n; ++i, (pw <<= 1) >= mod && (pw -= mod)) {
		if(i & 1)
			g[i] = 0;
		else {
			g[i] = (LL)g[i] * fct % mod * pw % mod * (pw - 1) % mod;
			if(!((i >> 1) & 1) && g[i])
				g[i] = mod - g[i];
		}
		if(i)
			fct = (LL)fct * i % mod;
	}
	int t, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int ret = 0;
		for(int i = 0; i <= n + 1; i += 2)
			(ret += g[i]) >= mod && (ret -= mod);
		printf("%d\n", ret);
	}
	return 0;
}
