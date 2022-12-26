#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
typedef complex<DB> Complex;
const DB pi = acos(-1.0);
const int maxd = 3, maxn = 1 << 16 | 1, maxe = 9, maxLen = 17, maxs = 1 << maxLen | 1;
typedef int Matrix[maxd][maxd];
int mod, BSFT, BMSK;
Complex w[maxs << 1 | 1];
void initFFT(int len) {
	int bitLen;
	for(bitLen = 0; (1 << bitLen) < len; ++bitLen);
	Complex *W = w + (1 << bitLen);
	for(int i = 0, ilim = 1 << bitLen; i < ilim; ++i) {
		int j = i, k = ilim >> 1; // 2 pi / ilim
		for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
		W[i] = Complex(cos(pi / k * j), sin(pi / k * j));
	}
	for(int i = (1 << bitLen) - 1; i > 0; --i)
		w[i] = w[i << 1];
	for(BSFT = 1; (1 << (BSFT << 1)) < mod; ++BSFT);
	BMSK = (1 << BSFT) - 1;
}
void FFT(int len, Complex x[], int flag) {
	register int i, j, k;
	for(i = 1, j = 0; i < len; ++i) {
		for(k = len >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			std::swap(x[i], x[j]);
	}
	register Complex *W = w + 1, t;
	for(i = 1; i < len; i <<= 1)
		for(j = 0, W += i; j < len; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = W[k] * x[i + j + k];
				x[i + j + k] = x[j + k] - t;
				x[j + k] = x[j + k] + t;
			}
	if(flag == -1) {
		std::reverse(x + 1, x + len);
		t = Complex(len, 0);
		for(i = 0; i < len; ++i)
			x[i] /= t;
	}
}
void polyMul(int len, int a[], int b[], int c[]) {
	static Complex A[maxs], B[maxs], C[maxs], tp1, tp2;
	for(int i = 0; i < len; ++i) {
		A[i] = Complex(a[i] & BMSK, a[i] >> BSFT);
		B[i] = Complex(b[i] & BMSK, b[i] >> BSFT);
	}
	FFT(len, A, 1);
	FFT(len, B, 1);
	for(int i = 0; i < len; ++i) {
		tp1 = conj(A[i ? len - i : 0]);
		tp2 = Complex(B[i].real() / 2, B[i].imag() / 2);
		B[i] = (A[i] + tp1) * tp2;
		tp2 = Complex(tp2.imag(), -tp2.real());
		C[i] = (A[i] - tp1) * tp2;
	}
	FFT(len, B, -1);
	FFT(len, C, -1);
	for(int i = 0; i < len; ++i) {
		int vLL = (LL)(B[i].real() + 0.5) % mod, vLH = (LL)(B[i].imag() + 0.5) % mod;
		int vHL = (LL)(C[i].real() + 0.5) % mod, vHH = (LL)(C[i].imag() + 0.5) % mod;
		c[i] = (((((LL)vHH << BSFT) + vHL + vLH) << BSFT) + vLL) % mod;
	}
}
int n, d, pw[maxn], f[maxs], g[maxs];
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
void initRoot() {
	int cnt = 0, pr[maxe];
	for(int i = 2, tmp = mod - 1; i <= tmp; ++i) {
		if(i * i > tmp)
			i = tmp;
		if(tmp % i == 0)
			for(pr[cnt++] = i; tmp % i == 0; tmp /= i);
	}
	int gen;
	for(gen = 2; gen < mod; ++gen) {
		bool flag = mod_pow(gen, mod - 1) == 1;
		for(int i = 0; i < cnt && flag; ++i)
			flag &= mod_pow(gen, (mod - 1) / pr[i]) != 1;
		if(flag)
			break;
	}
	pw[0] = 1;
	pw[1] = mod_pow(gen, (mod - 1) / n);
	for(int i = 2; i < n; ++i)
		pw[i] = (LL)pw[i - 1] * pw[1] % mod;
}
void matMul(Matrix const &lft, Matrix const &rht, Matrix &ret) {
	static Matrix tmp;
	for(int i = 0; i < d; ++i) {
		for(int j = 0; j < d; ++j)
			tmp[i][j] = 0;
		for(int j = 0; j < d; ++j)
			for(int k = 0; k < d; ++k)
				tmp[i][k] = (tmp[i][k] + (LL)lft[i][j] * rht[j][k]) % mod;
	}
	for(int i = 0; i < d; ++i)
		for(int j = 0; j < d; ++j)
			ret[i][j] = tmp[i][j];
}
int main() {
	int ex, u, v;
	Matrix A, B, C;
	scanf("%d%d%d%d%d%d", &d, &n, &ex, &u, &v, &mod);
	--u;
	--v;
	for(int i = 0; i < d; ++i)
		for(int j = 0; j < d; ++j)
			scanf("%d", A[i] + j);
	initRoot();
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < d; ++j)
			for(int k = 0; k < d; ++k) {
				B[j][k] = j == k ? 1 : 0;
				C[j][k] = ((LL)A[j][k] * pw[i] + B[j][k]) % mod;
			}
		for(int j = ex; j > 0; j >>= 1) {
			if(j & 1)
				matMul(B, C, B);
			if(j > 1)
				matMul(C, C, C);
		}
		f[n - 1 - i] = (LL)pw[i * (i - 1LL) / 2 % n] * B[u][v] % mod;
	}
	for(int i = 0; i <= ((n - 1) << 1); ++i) {
		int pos = i * (i - 1LL) / 2 % n;
		g[i] = pw[pos ? n - pos : 0];
	}
	int len;
	for(len = 1; len + 1 < n + n; len <<= 1);
	initFFT(len);
	polyMul(len, f, g, f);
	for(int i = 0, ivs = mod_pow(n, mod - 2); i < n; ++i) {
		int res = (LL)pw[i * (i - 1LL) / 2 % n] * f[n - 1 + i] % mod * ivs % mod;
		printf("%d\n", res);
	}
	return 0;
}
