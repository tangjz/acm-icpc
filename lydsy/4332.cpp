#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB pi = acos(-1.0);
const int maxn = (int)1e4 + 1, maxLen = 16, maxs = 1 << maxLen | 1;
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
void polyInv(int mod, int n, int cur[], int nxt[]) {
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
			A[i] = i < len ? Complex((int)(A[i + len].r + 0.5) % mod, 0) : Complex();
		FFT(len + len, A, 1);
		for(int i = 0; i < len + len; ++i)
			A[i] = A[i] * B[i];
		FFT(len + len, A, -1);
		for(int i = len; i < upp; ++i) {
			nxt[i] = (int)(A[i - len].r + 0.5) % mod;
			if(nxt[i])
				nxt[i] = mod - nxt[i];
		}
	}
}
int intPow(int mod, int k, int x) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = x * x % mod)
		if(k & 1)
			ret = ret * x % mod;
	return ret;
}
void DFT(int mod, vector<int> &vec, int len, Complex dft[], int flag) {
	vector<int>::iterator it = vec.begin();
	if(flag == 1) {
		for(int i = 0; i < len; ++i)
			dft[i] = it != vec.end() ? Complex(*(it++), 0) : Complex();
		FFT(len, dft, 1);
	} else {
		FFT(len, dft, -1);
		for(int i = 0; it != vec.end(); ++i)
			*(it++) = (int)(dft[i].r + 0.5) % mod;
	}
}
void polyPow(int mod, int pr, int k, vector<int> &f) {
	bool isZero = 1;
	for(vector<int>::iterator it = f.begin(); it != f.end(); ++it)
		isZero &= !(*it);
	if(isZero)
		return;
	if(f.size() == 1) {
		int phi = mod - mod / pr;
		f[0] = intPow(mod, k < phi ? k : k % phi + phi, f[0]);
		return;
	}
	int len, upp = (int)f.size();
	for(len = 1; len + 1 < upp + upp; len <<= 1);
	vector<int> g;
	g.reserve(upp);
	if(k < mod) {
		DFT(mod, f, len, A, 1);
		for(int u = k; u > 0; u >>= 1) {
			if(u & 1) {
				if(!g.size()) {
					g = f;
				} else {
					DFT(mod, g, len, B, 1);
					for(int i = 0; i < len; ++i)
						B[i] = A[i] * B[i];
					DFT(mod, g, len, B, -1);
				}
			}
			if(u > 1) {
				for(int i = 0; i < len; ++i)
					A[i] = A[i] * A[i];
				DFT(mod, f, len, A, -1);
				DFT(mod, f, len, A, 1);
			}
		}
		if(!g.size()) {
			g.resize(upp);
			g[0] = 1;
		}
		f.swap(g);
		return;
	}
	vector<int> h;
	h.reserve(upp);
	DFT(mod, f, len, A, 1);
	for(int u = k % mod, v = mod; v > 0; u >>= 1, v >>= 1) {
		if(u & 1) {
			if(!g.size()) {
				g = f;
			} else {
				DFT(mod, g, len, B, 1);
				for(int i = 0; i < len; ++i)
					B[i] = A[i] * B[i];
				DFT(mod, g, len, B, -1);
			}
		}
		if(v & 1) {
			if(!h.size()) {
				h = f;
			} else {
				DFT(mod, h, len, B, 1);
				for(int i = 0; i < len; ++i)
					B[i] = A[i] * B[i];
				DFT(mod, h, len, B, -1);
			}
		}
		if(v > 1) {
			for(int i = 0; i < len; ++i)
				A[i] = A[i] * A[i];
			DFT(mod, f, len, A, -1);
			DFT(mod, f, len, A, 1);
		}
	}
	int upp2 = (upp - 1) / pr + 1;
	for(int i = 1, j = pr; i < upp2; ++i, j += pr)
		h[i] = h[j];
	h.resize(upp2);
	polyPow(mod, pr, k / mod, h);
	h.resize(upp);
	for(int i = upp2 - 1, j = i * pr; i > 0; --i, j -= pr) {
		h[j] = h[i];
		h[i] = 0;
	}
	if(!g.size()) {
		f.swap(h);
		return;
	}
	DFT(mod, g, len, A, 1);
	DFT(mod, h, len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	DFT(mod, f, len, A, -1);
}
void polyPow(int mod, int k, int len, int cur[], int nxt[]) {
	memset(nxt, 0, len * sizeof(int));
	for(int pr = 2, rem = mod; pr <= rem; ++pr) {
		if(pr * pr > rem)
			pr = rem;
		if(rem % pr > 0)
			continue;
		int pw, mul;
		for(pw = pr, rem /= pr; rem % pr == 0; pw *= pr, rem /= pr);
		mul = mod / pw;
		mul = mul * intPow(pw, pw - pw / pr - 1, mul % pw) % mod;
		int sta = 0;
		for( ; sta <= len && cur[sta] % pw == 0; ++sta);
		int len2 = len - sta * k;
		if(len2 <= 0)
			continue;
		vector<int> f;
		f.reserve(len2);
		for(int i = 0, j = sta; i < len2; ++i, ++j)
			f.push_back(cur[j] % pw);
		polyPow(pw, pr, k, f);
		for(int i = 0, j = sta * k; i < len2; ++i, ++j)
			nxt[j] += mul * f[i];
	}
	for(int i = 0; i < len; ++i)
		if(nxt[i] >= mod)
			nxt[i] %= mod;
}
int n, k, mod, f[maxn], g[maxn], h[maxn], ans;
int main() {
	int c[3];
	scanf("%d%d%d%d%d%d", &n, &mod, &k, c + 2, c + 1, c + 0);
	f[0] = 1;
	for(int i = 1; i <= n; ++i) {
		f[i] = ((c[2] * i + c[1]) * i + c[0]) % mod;
		if(f[i])
			f[i] = mod - f[i];
	}
	initFFT(n << 1 | 1);
	polyInv(mod, n, f, g);
	f[0] = 0;
	for(int i = 1; i <= n; ++i)
		if(f[i]) {
			f[i] = mod - f[i];
			ans = (ans + f[i] * g[n - i]) % mod;
		}
	if(k < n) {
		polyPow(mod, k + 1, n + 1, f, h);
		for(int i = 1; i <= n; ++i)
			if(h[i]) {
				h[i] = mod - h[i];
				ans = (ans + h[i] * g[n - i]) % mod;
			}
	}
	printf("%d\n", ans);
	return 0;
}
