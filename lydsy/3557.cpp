#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB pi = acos(-1.0);
const int maxn = (int)1e6 + 1, maxLen = 21, maxs = 1 << maxLen | 1;
struct Complex {
	DB r, i;
	Complex() { r = i = 0; }
	Complex(DB r, DB i) : r(r), i(i) {}
	Complex operator + (Complex const &t) const { return Complex(r + t.r, i + t.i); }
	Complex operator - (Complex const &t) const { return Complex(r - t.r, i - t.i); }
	Complex operator * (Complex const &t) const { return Complex(r * t.r - i * t.i, r * t.i + i * t.r); }
} w[maxs << 1 | 1], A[maxs], B[maxs];
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
			// x[i].i /= len;
		}
	}
}
void polyInv(int n, int cur[], int nxt[]) {
	nxt[0] = 1;
	for(int len = 1; len < n; len <<= 1) {
		int upp = min(len + len, n);
		for(int i = 0; i < len + len; ++i) {
			A[i] = i < upp ? Complex(cur[i], 0) : Complex();
			B[i] = i < len ? Complex(nxt[i], 0) : Complex();
		}
		FFT(len + len, A, 1);
		FFT(len + len, B, 1);
		for(int i = 0; i < len + len; ++i)
			A[i] = A[i] * B[i];
		FFT(len + len, A, -1);
		for(int i = 0; i < len + len; ++i)
			A[i] = i < len ? Complex((int)(A[i + len].r + 0.5) & 1, 0) : Complex();
		FFT(len + len, A, 1);
		for(int i = 0; i < len + len; ++i)
			A[i] = A[i] * B[i];
		FFT(len + len, A, -1);
		for(int i = len; i < upp; ++i)
			nxt[i] = (int)(A[i - len].r + 0.5) & 1;
	}
}
void polyMul(int aLen, int a[], int bLen, int b[], int cLen, int c[]) {
	int len, plen = aLen + bLen - 1;
	for(len = 1; len < plen; len <<= 1);
	for(int i = 0; i < len; ++i) {
		A[i] = i < aLen ? Complex(a[i], 0) : Complex();
		B[i] = i < bLen ? Complex(b[i], 0) : Complex();
	}
	FFT(len, A, 1);
	if(aLen == bLen && a == b) {
		memcpy(B, A, len * sizeof(Complex));
	} else {
		FFT(len, B, 1);
	}
	for(int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	FFT(len, A, -1);
	for(int i = 0; i < cLen; ++i)
		c[i] = (int)(A[i].r + 0.5) & 1;
}
int n, len, p[maxn], q[maxn];
void polyMerge(int aLen, int a[], int bLen, int b[], int &cLen, int c[]) {
	int tLen = aLen + bLen - 1;
	static int tmp[maxn << 1 | 1];
	polyMul(aLen, a, bLen, b, tLen, tmp);
	if(tLen <= n) {
		cLen = tLen;
		memcpy(c, tmp, cLen * sizeof(int));
		return;
	}
	int dLen = tLen - n;
	static int d[maxn];
	reverse(tmp, tmp + tLen);
	polyMul(dLen, tmp, dLen, q, dLen, d);
	reverse(tmp, tmp + tLen);
	reverse(d, d + dLen);
	for(int i = 0; i < len; ++i) {
		A[i] = i <= n ? Complex(p[i], 0) : Complex();
		B[i] = i < dLen ? Complex(d[i], 0) : Complex();
	}
	if(n == len)
		A[0].r += p[n];
	FFT(len, A, 1);
	FFT(len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	FFT(len, A, -1);
	for(int i = 0, j = len; i < n; ++i, ++j) {
		tmp[i] ^= (int)(A[i].r + 0.5) & 1;
		if(j < tLen)
			tmp[i] ^= tmp[j];
	}
	cLen = n;
	memcpy(c, tmp, cLen * sizeof(int));
	for( ; cLen && !c[cLen - 1]; --cLen);
}
int typ, dt, aLen, a[maxn], bLen, b[maxn], cLen, c[maxn];
int main() {
	scanf("%d", &n);
	initFFT((n - 1) << 1 | 1);
	for(int i = 0; i < n; ++i)
		scanf("%d", p + i);
	p[n] = 1;
	reverse(p, p + n + 1);
	polyInv(n - 1, p, q);
	reverse(p, p + n + 1);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(aLen = n; aLen && !a[aLen - 1]; --aLen);
	for(len = 1; len < n; len <<= 1);
	scanf("%d%d", &typ, &dt);
	if(!typ) {
		bLen = dt % n + 1;
		memset(b, 0, bLen * sizeof(int));
		b[bLen - 1] = 1;
		memcpy(c, p, n * sizeof(int));
		for(cLen = n; cLen && !c[cLen - 1]; --cLen);
		for(int k = dt / n; k > 0; k >>= 1) {
			if(k & 1)
				polyMerge(bLen, b, cLen, c, bLen, b);
			if(k > 1)
				polyMerge(cLen, c, cLen, c, cLen, c);
		}
		polyMerge(aLen, a, bLen, b, aLen, a);
	} else {
		dt %= n;
		for(int i = 0; i < n; ++i)
			scanf("%d", b + i);
		for(bLen = n; bLen && !b[bLen - 1]; --bLen);
		if(dt > 0) {
			for(int i = dt; i < n; ++i) {
				polyMerge(aLen, a, aLen, a, aLen, a);
				polyMerge(bLen, b, bLen, b, bLen, b);
			}
			cLen = aLen;
			memcpy(c, a, cLen * sizeof(int));
			for(int i = 1; i < dt; ++i) {
				polyMerge(cLen, c, cLen, c, cLen, c);
				polyMerge(aLen, a, cLen, c, aLen, a);
			}
			polyMerge(aLen, a, bLen, b, aLen, a);
		} else {
			aLen = bLen;
			memcpy(a, b, aLen * sizeof(int));
		}
	}
	static char buf[maxn];
	for(int i = 0; i < n; ++i)
		buf[i] = "01"[i < aLen && a[i]];
	buf[n] = '\0';
	puts(buf);
	return 0;
}
