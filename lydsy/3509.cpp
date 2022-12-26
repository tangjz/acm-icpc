#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi = acos(-1.0);
const int maxn = (int)1e5 + 1, maxv = (int)3e4 + 1, maxLen = 15, maxs = 1 << maxLen | 1;
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
			swap(x[i], x[j]);
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
		reverse(x + 1, x + len);
		for(i = 0; i < len; ++i) {
			x[i].r /= len;
			x[i].i /= len;
		}
	}
}
int n, a[maxn], m, len, cL[maxv], cR[maxv];
LL ans, cM[maxv];
int main() {
	scanf("%d", &n);
	int low = maxv, upp = -1;
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		low = min(low, a[i]);
		upp = max(upp, a[i]);
	}
	for(int i = 0; i < n; ++i) {
		a[i] -= low;
		++cR[a[i]];
	}
	upp -= low;
	for(len = 0; (1 << len) <= upp; ++len);
	m = max((int)floor(n / max(sqrt((3 * len) << len), 1.0)), 1);
	len = 1 << len;
	initFFT(len);
	for(int i = 0, L = 0, R; i < m; ++i, L = R) {
		R = L + n / m + (i < n % m);
		for(int j = L; j < R; ++j)
			--cR[a[j]];
		memset(cM, 0, (upp + 1) * sizeof(LL));
		if(i && i + 1 < m) {
			static Complex A[maxs], B[maxs], C[maxs];
			for(int i = 0; i < len; ++i)
				if(i + i <= upp) {
					A[i] = Complex(cL[i << 1], cL[i << 1 | 1]);
					B[i] = Complex(cR[i << 1], cR[i << 1 | 1]);
				} else {
					A[i] = B[i] = Complex();
				}
			FFT(len, A, 1);
			FFT(len, B, 1);
			for(int i = 0; i < len; ++i) {
				int j = i ? len - i : 0;
				Complex u = Complex((A[i].r + A[j].r) / 2, (A[i].i - A[j].i) / 2) * Complex((B[i].r + B[j].r) / 2, (B[i].i - B[j].i) / 2);
				Complex v = Complex((A[i].i + A[j].i) / 2, (A[j].r - A[i].r) / 2) * Complex((B[i].i + B[j].i) / 2, (B[j].r - B[i].r) / 2);
				C[i] = Complex(u.r - v.i, u.i + v.r);
			}
			FFT(len, C, -1);
			for(int i = 0; i <= upp; ++i) {
				cM[i] += (LL)(C[i].r + 0.5);
				cM[i + 1] += (LL)(C[i].i + 0.5);
			}
		}
		for(int j = L; j < R; ++j) {
			for(int k = j + 1; k < R; ++k) {
				int u = a[j] + a[j] - a[k], v = a[k] + a[k] - a[j];
				if(u >= 0 && u <= upp)
					ans += cL[u];
				if(v >= 0 && v <= upp)
					ans += cR[v];
			}
			ans += cM[a[j]];
			++cL[a[j]];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
