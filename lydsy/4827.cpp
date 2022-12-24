#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB pi = acos(-1.0);
const int maxLen = 17, maxs = 1 << maxLen | 1;
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
int n, len, coeff[3];
Complex A[maxs], B[maxs];
int main() {
	scanf("%d%*d", &n);
	for(len = 1; len + 1 < n + n; len <<= 1);
	for(int i = 0, x; i < n; ++i) {
		scanf("%d", &x);
		coeff[0] += x * x;
		coeff[1] += x;
		A[i].r = x;
	}
	for(int i = 0, x; i < n; ++i) {
		scanf("%d", &x);
		coeff[0] += x * x;
		coeff[1] -= x;
		B[n - 1 - i].r = x;
	}
	initFFT(len);
	FFT(len, A, 1);
	FFT(len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	FFT(len, A, -1);
	int upp = (int)(A[0].r + 0.5) + (int)(A[n].r + 0.5);
	for(int i = 1; i < n; ++i) {
		int tmp = (int)(A[i].r + 0.5) + (int)(A[n + i].r + 0.5);
		if(upp < tmp)
			upp = tmp;
	}
	coeff[0] -= upp << 1;
	coeff[1] <<= 1;
	coeff[2] = n;
	int x = -coeff[1] / (coeff[2] << 1), ans = (coeff[2] * x + coeff[1]) * x + coeff[0];
	for(int i = x - 1; i <= x + 1; i += 2) {
		int tmp = (coeff[2] * i + coeff[1]) * i + coeff[0];
		if(ans > tmp)
			ans = tmp;
	}
	printf("%d\n", ans);
	return 0;
}