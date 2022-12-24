#include <bits/stdc++.h>
using namespace std;
namespace fastIO{
	#define MAXB (1 << 20 | 1)
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
	struct Output {
		char buf[MAXB], *ptr, *end;
		Output() {
			ptr = buf;
			end = buf + MAXB;
		}
		void print(char ch) {
			if(ptr == end) {
				fwrite(buf, 1, MAXB, stdout);
				ptr = buf;
			}
			*(ptr++) = ch;
		}
		void println(long long x) {
			static char pat[23];
			sprintf(pat, "%lld\n", x);
			for(char *ptr = pat; *ptr; ++ptr)
				print(*ptr);
		}
		~Output() {
			if(ptr != buf)
				fwrite(buf, 1, ptr - buf, stdout);
		}
	} out;
	#undef BUF_SIZE
}
typedef long long LL;
typedef double DB;
const DB pi = acos(-1.0);
const int maxLen = 16, maxs = 1 << maxLen | 1, maxd = 1 << 6 | 1;
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
		for(i = 0; i < len; ++i) {
			x[i].r /= len;
			x[i].i /= len;
		}
	}
}
int t, n, m, q, cL[maxs], cR[maxs];
LL ans[maxs << 1 | 1];
void solve(int L, int R) {
	if(R - L < maxd) {
		for(int i = L; i <= R; ++i)
			if(cL[i])
				for(int j = L; j <= R; ++j)
					if(cR[j])
						ans[i < j ? i + j : i - j] += (LL)cL[i] * cR[j];
		return;
	}
	int M = (L + R) >> 1;
	solve(L, M);
	solve(M + 1, R);
	int len, plen = M - L + 1, qlen = R - M;
	for(len = 1; len < plen + qlen - 1; len <<= 1);
	static Complex A[maxs], B[maxs], C[maxs], tp1, tp2;
	for(int i = 0; i < len; ++i) {
		A[i] = i < plen ? Complex(cL[L + i], cR[M - i]) : Complex();
		B[i] = i < qlen ? Complex(cR[M + 1 + i], cL[M + 1 + i]) : Complex();
	}
	FFT(len, A, 1);
	FFT(len, B, 1);
	for(int i = 0; i < len; ++i) {
		int j = i ? len - i : 0;
		tp1 = Complex((A[i].r + A[j].r) / 2, (A[i].i - A[j].i) / 2) * Complex((B[i].r + B[j].r) / 2, (B[i].i - B[j].i) / 2);
		tp2 = Complex((A[i].i + A[j].i) / 2, (A[j].r - A[i].r) / 2) * Complex((B[i].i + B[j].i) / 2, (B[j].r - B[i].r) / 2);
		C[i] = Complex(tp1.r - tp2.i, tp1.i + tp2.r);
	}
	FFT(len, C, -1);
	for(int i = 0; i < plen + qlen - 1; ++i) {
		ans[L + M + 1 + i] += (LL)(C[i].r + 0.5);
		ans[1 + i] += (LL)(C[i].i + 0.5);
	}
}
int main() {
	initFFT(1 << maxLen);
	fastIO::nextInt(t);
	while(t--) {
		fastIO::nextInt(n);
		fastIO::nextInt(m);
		fastIO::nextInt(q);
		int low = 0, upp = 0;
		for(int i = 0, x; i < n + m; ++i) {
			fastIO::nextInt(x);
			for( ; upp <= x; ++upp)
				cL[upp] = cR[upp] = 0;
			++(i < n ? cL : cR)[x];
		}
		for( ; !cL[low] && !cR[low]; ++low);
		memset(ans, 0, (upp << 1) * sizeof(LL));
		solve(low, upp - 1);
		for(int i = 0, x; i < q; ++i) {
			fastIO::nextInt(x);
			fastIO::out.println(x < upp + upp ? ans[x] : 0);
		}
	}
	return 0;
}