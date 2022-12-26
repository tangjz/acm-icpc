#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB pi = acos(-1.0);
const int maxn = (int)1e5 + 1, maxLen = 18, maxs = 1 << maxLen | 1;
struct Complex {
	DB r, i;
	Complex() { r = i = 0; }
	Complex(DB r, DB i) : r(r), i(i) {}
	Complex operator + (Complex const &t) const {
		return Complex(r + t.r, i + t.i);
	}
	Complex operator - (Complex const &t) const {
		return Complex(r - t.r, i - t.i);
	}
	Complex operator * (Complex const &t) const {
		return Complex(r * t.r - i * t.i, r * t.i + i * t.r);
	}
} w[maxs << 1 | 1];
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
int n, len;
DB f[maxn];
Complex A[maxs], B[maxs];
int main() {
	scanf("%d", &n);
	for(len = 1; len + 1 < n + n; len <<= 1);
	for(int i = 0; i < n; ++i) {
		scanf("%lf", f + i);
		A[i].r = f[i];
		if(i > 0) {
			B[i].r = 1.0 / i / i;
			B[len - i].r = -B[i].r;
		}
	}
	initFFT(len);
	FFT(len, A, 1);
	FFT(len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	FFT(len, A, -1);
	for(int i = 0; i < n; ++i)
		printf("%.3f\n", A[i].r);
	return 0;
}
