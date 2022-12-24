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
		void print(int x, char endc = '\0') {
			static char pat[13];
			sprintf(pat, "%d%c", x, endc);
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
const int maxn = (int)5e4 + 1, maxLen = 17, maxs = 1 << maxLen | 1, mod = 998244353, gen = 3, inv2 = (mod + 1) >> 1;
int n, m, a[maxn], w[maxs << 1 | 1];
vector<int> f[3], g;
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
}
inline void mod_inc(int &x, int y) {
	x = mod_add(x, y);
}
void initNTT(int len) {
	int bitLen;
	for(bitLen = 0; (1 << bitLen) < len; ++bitLen);
	int *W = w + (1 << bitLen);
	W[0] = W[1] = 1;
	for(int i = (mod - 1) >> bitLen, x = gen; i > 0; i >>= 1, x = (LL)x * x % mod)
		if(i & 1)
			W[1] = (LL)W[1] * x % mod;
	for(int i = 2; i < (1 << bitLen); ++i)
		W[i] = (LL)W[i - 1] * W[1] % mod;
	for(int i = (1 << bitLen) - 1; i > 0; --i)
		w[i] = w[i << 1];
}
void NTT(int len, int x[], int flag) {
	static int bitLen = 0, ivs = 1, bitRev[maxs] = {};
	if(len != (1 << bitLen)) {
		for(bitLen = 0, ivs = 1; (1 << bitLen) < len; ++bitLen, ivs = (LL)ivs * inv2 % mod);
		for(int i = 1; i < len; ++i)
		    bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
	}
	for(int i = 1; i < len; ++i)
		if(i < bitRev[i])
			swap(x[i], x[bitRev[i]]);
	for(int d = 1; d < len; d <<= 1)
		for(int j = 0, *W = w + (d << 1); j < len; j += d << 1)
			for(int k = 0, *X = x + j; k < d; ++k) {
				int t = (LL)W[k] * X[k + d] % mod;
				X[d + k] = mod_add(X[k], mod - t);
				X[k] = mod_add(X[k], t);
			}
	if(flag == -1) {
		reverse(x + 1, x + len);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * ivs % mod;
	}
}
void polyMul(vector<int> const &lft, vector<int> const &rht, vector<int> &ret) {
	int len, szL = lft.size(), szR = rht.size();
	for(len = 1; len < szL + szR - 1; len <<= 1);
	static int a[maxs], b[maxs];
	for(int i = 0; i < szL; ++i)
		a[i] = lft[i];
	memset(a + szL, 0, (len - szL) * sizeof(int));
	NTT(len, a, 1);
	for(int i = 0; i < szR; ++i)
		b[i] = rht[i];
	memset(b + szR, 0, (len - szR) * sizeof(int));
	NTT(len, b, 1);
	for(int i = 0; i < len; ++i)
		a[i] = (LL)a[i] * b[i] % mod;
	NTT(len, a, -1);
	len = szL + szR - 1;
	ret.resize(len);
	for(int i = 0; i < len; ++i)
		ret[i] = a[i];
}
int main() {
	fastIO::nextInt(n);
	for(int i = 0; i < n; ++i) {
		fastIO::nextInt(a[i]);
		m = max(m, a[i]);
	}
	initNTT(m * 3 + 1);
	f[0].resize(m + 1);
	for(int i = 0; i < n; ++i)
		++f[0][a[i]];
	polyMul(f[0], f[0], f[1]);
	polyMul(f[0], f[1], f[2]);
	g.resize(m << 1 | 1);
	for(int i = 0; i <= m; ++i) {
		int x = g[i << 1] = f[0][i];
		mod_inc(f[1][i << 1], mod - x);
		x = mod_add(x, x);
		mod_inc(f[1][i], x);
		mod_inc(f[2][i * 3], x);
	}
	polyMul(f[0], g, g);
	for(int i = 0; i <= (m << 1); ++i)
		mod_inc(g[i], mod - f[1][i]);
	const int inv6 = (mod + 1) / 6;
	for(int i = 0; i <= m * 3; ++i) {
		int x = mod - g[i], y = f[2][i];
		mod_inc(y, mod_add(x, mod_add(x, x)));
		if(y) {
			y = (LL)y * inv6 % mod;
			fastIO::out.print(i, ' ');
			fastIO::out.print(y, '\n');
		}
	}
	return 0;
}