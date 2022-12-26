#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB pi = acos(-1.0);
const int maxn = 701, maxLen = 20, maxs = 1 << maxLen | 1;
struct Complex {
	DB r, i;
	Complex() { r = i = 0; }
	Complex(DB _r, DB _i) : r(_r), i(_i) {}
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
int n, m;
char buf[maxn][maxn];
Complex A[maxs], B[maxs];
void dfs(int x, int y, int idx) {
	if(x < 0 || x >= n || y < 0 || y >= m || buf[x][y] != 'x')
		return;
	buf[x][y] = '.';
	A[idx].r = 1;
	dfs(x, y - 1, idx - 1);
	dfs(x, y + 1, idx + 1);
	dfs(x - 1, y, idx - m);
	dfs(x + 1, y, idx + m);
}
int main() {
	scanf("%d%d", &n, &m);
	int len;
	for(len = 1; len + 1 < 2 * n * m; len <<= 1);
	initFFT(len);
	int xL = n, xR = -1, yL = m, yR = -1;
	for(int i = 0, idx = 0; i < n; ++i) {
		scanf("%s", buf[i]);
		for(int j = 0; j < m; ++j, ++idx)
			if(buf[i][j] == '#') {
				A[idx].r = 1;
			} else if(buf[i][j] == 'o') {
				xL = min(xL, i);
				xR = max(xR, i);
				yL = min(yL, j);
				yR = max(yR, j);
			}
	}
	FFT(len, A, 1);
	for(int i = xL; i <= xR; ++i)
		for(int j = yL; j <= yR; ++j)
			if(buf[i][j] == 'o') {
				int idx = (i - xL) * m + (j - yL);
				B[idx ? len - idx : 0].r = 1;
			}
	FFT(len, B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	FFT(len, A, -1);
	if((len >> 1) >= n * m)
		len >>= 1;
	for(int i = 0; i < len; ++i)
		B[i] = Complex();
	for(int i = xL; i <= xR; ++i)
		for(int j = yL; j <= yR; ++j)
			if(buf[i][j] == 'o') {
				int idx = (i - xL) * m + (j - yL);
				B[idx].r = 1;
			}
	FFT(len, B, 1);
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx)
			if(i - xL + xR < n && j - yL + yR < m && (int)(A[idx].r + 0.5) == 0)
				buf[i][j] = 'x';
	for(int i = 0; i < len; ++i)
		A[i] = Complex();
	dfs(xL, yL, xL * m + yL);
	FFT(len, A, 1);
	for(int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	FFT(len, A, -1);
	int ans = 0;
	for(int idx = 0; idx < n * m; ++idx)
		ans += (int)(A[idx].r + 0.5) > 0;
	printf("%d\n", ans);
	return 0;
}
