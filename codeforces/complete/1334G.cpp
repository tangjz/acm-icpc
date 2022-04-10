#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = (int)2e5 + 1, maxc = 26, maxLen = 18, maxs = 1 << maxLen | 1;
const DB pi = acos(-1.0); // double
struct Complex {
	DB r, i;
	Complex() { r = i = 0; }
	Complex(DB r, DB i) : r(r), i(i) {}
	Complex operator + (Complex const &t) const { return Complex(r + t.r, i + t.i); }
	Complex operator - (Complex const &t) const { return Complex(r - t.r, i - t.i); }
	Complex operator * (Complex const &t) const { return Complex(r * t.r - i * t.i, r * t.i + i * t.r); }
} w[maxs], A[maxs], B[maxs];
void FFT_init(int len) {
	register int i, j, k;
	for(i = 1; i < len; i <<= 1)
		for(j = 0, k = i; j < i; ++j, ++k)
			w[k] = k & 1 ? Complex(cos(pi / i * j), sin(pi / i * j)) : w[k >> 1];
}
void FFT(int n, Complex x[], int flag) {
	register int i, j, k;
	for(i = 1, j = 0; i < n; ++i) {
		for(k = n >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j) std::swap(x[i], x[j]);
	}
	static Complex *W, t;
	for(i = 1; i < n; i <<= 1)
		for(j = 0, W = w + i; j < n; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = W[k] * x[i + j + k];
				x[i + j + k] = x[j + k] - t;
				x[j + k] = x[j + k] + t;
			}
	if(flag != -1) return;
	std::reverse(x + 1, x + n);
	for(i = 0; i < n; ++i)
		x[i].r /= n; // x[i].i /= n;
}
int n, m, perm[maxc + 1];
char buf[maxn], pat[maxn];
bool ban[maxn];
int main() {
	for(int i = 0; i < maxc; ++i) {
		scanf("%d", perm + i);
		--perm[i];
	}
	scanf("%s%s", pat, buf);
	n = strlen(buf);
	m = strlen(pat);
	int len;
	for(len = 1; len < n; len <<= 1);
	FFT_init(len);
	for(int i = 0; i < maxc; ++i) {
		int cnt = 0;
		char ch0 = 'a' + i, ch1 = 'a' + perm[i];
		for(int j = 0; j < len; ++j) {
			A[j] = Complex(j < n && (buf[j] == ch0 || buf[j] == ch1) ? 1 : 0, 0);
			B[j ? len - j : j] = Complex(j < m && pat[j] == ch0 ? 1 : 0, 0);
			cnt += j < m && pat[j] == ch0;
		}
		if(!cnt)
			continue;
		FFT(len, A, 1);
		FFT(len, B, 1);
		for(int j = 0; j < len; ++j)
			A[j] = A[j] * B[j];
		FFT(len, A, -1);
		for(int j = 0; j <= n - m; ++j)
			ban[j] |= (int)(A[j].r + 0.5) < cnt;
	}
	for(int i = 0; i <= n - m; ++i)
		buf[i] = "10"[ban[i]];
	buf[n - m + 1] = '\0';
	puts(buf);
	return 0;
}