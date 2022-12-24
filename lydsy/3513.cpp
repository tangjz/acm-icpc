#include <bits/stdc++.h>
using namespace std;
namespace fastIO{
	#define MAXB (4 << 20 | 1)
	bool isEOF = 0;
	inline char next() {
		static char buf[MAXB], *ptr = buf + MAXB, *end = ptr;
		if(ptr == end) {
			ptr = buf;
			end = buf + fread(buf, 1, MAXB, stdin);
			if(ptr == end) {
				isEOF = 1;
				return EOF;
			}
		}
		return *(ptr++);
	}
	inline bool isBlank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void nextChar(char &ch) {
		while(isBlank(ch = next()));
	}
	inline void nextInt(int &x) {
		char ch;
		while(isBlank(ch = next()));
		if(isEOF)
			return;
		bool sign = ch == '-';
		x = sign ? 0 : (ch - '0');
		while((ch = next()) >= '0' && ch <= '9')
			x = x * 10 + (ch - '0');
		if(sign)
			x = -x;
	}
	#undef BUF_SIZE
}
typedef long long LL;
typedef double DB;
const DB pi = acos(-1.0);
const int maxn = (int)1e5 + 1, maxLen = 18, maxs = 1 << maxLen | 1;
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
		for(i = 0; i < len; ++i)
			x[i].r /= len;
	}
}
int t, n, m, a[maxn];
Complex A[maxs];
int main() {
	initFFT((maxn - 3) << 1 | 1);
	fastIO::nextInt(t);
	while(t--) {
		fastIO::nextInt(n);
		LL num = n * (n - 1LL) * (n - 2) / 6, den = num;
		m = 0;
		while(n--) {
			int x;
			fastIO::nextInt(x);
			for( ; m <= x; ++m)
				a[m] = 0;
			++a[x];
		}
		int low;
		for(low = 0; !a[low]; ++low);
		if(low + low >= m) {
			printf("%.7f\n", 1.0);
			continue;
		}
		for(n = 1; n + 1 < (m << 1) - (low << 2); n <<= 1);
		for(int i = 0; i < n; ++i)
			A[i] = i + (low << 1) < m ? Complex(a[i + low], 0) : Complex();
		FFT(n, A, 1);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * A[i];
		FFT(n, A, -1);
		LL cnt = 0;
		for(int i = low + low; i < m; ++i) {
			cnt += (LL)(A[i - (low << 1)].r + 0.5) - (i & 1 ? 0 : a[i >> 1]);
			if(a[i])
				num -= a[i] * (cnt >> 1);
		}
		printf("%.7f\n", (DB)num / den);
	}
	return 0;
}