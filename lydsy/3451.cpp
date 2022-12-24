#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB pi = acos(-1.0);
const int maxn = (int)3e4 + 1, maxLen = 17, maxs = 1 << maxLen | 1;
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
void polySquare(int aLen, int a[], int bLen, int b[]) {
	int len;
	static Complex A[maxs];
	for(len = 1; len + 1 < aLen + aLen; len <<= 1);
	for(int i = 0; i < len; ++i)
		A[i] = i < aLen ? Complex(a[i], 0) : Complex();
	FFT(len, A, 1);
	for(int i = 0; i < len; ++i)
		A[i] = A[i] * A[i];
	FFT(len, A, -1);
	for(int i = 0; i < bLen; ++i)
		b[i] = (int)(A[i].r + 0.5);
}
int n, tot, ord[maxn], par[maxn];
vector<int> e[maxn];
bool ban[maxn];
void bfs(int rt, int up = -1) {
	tot = 0;
	par[rt] = up;
	ord[tot++] = rt;
	for(int i = 0; i < tot; ++i) {
		int u = ord[i];
		for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
			int v = *it;
			if(v != par[u] && !ban[v]) {
				par[v] = u;
				ord[tot++] = v;
			}
		}
	}
}
int ans[maxn], len[3], f[3][maxn], g[maxn];
void solve(int rt) {
	bfs(rt);
	int cnt = tot;
	for(int i = tot - 1; i >= 0; --i) {
		int u = ord[i], mx = 0;
		g[u] = 1;
		for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
			int v = *it;
			if(v != par[u] && !ban[v]) {
				g[u] += g[v];
				mx = max(mx, g[v]);
			}
		}
		mx = max(mx, tot - g[u]);
		if(mx < cnt) {
			rt = u;
			cnt = mx;
		}
	}
	cnt = tot;
	ban[rt] = 1;
	int &PLEN = len[0], *PF = f[0];
	int &LEN = len[1], *F = f[1];
	int &CLEN = len[2], *CF = f[2];
	PLEN = PF[0] = 1;
	for(vector<int>::iterator it = e[rt].begin(); it != e[rt].end(); ++it) {
		int tr = *it;
		if(ban[tr])
			continue;
		bfs(tr, rt);
		LEN = F[0] = 1;
		if(PLEN > 1) {
			++PF[1];
		} else {
			PF[PLEN++] = 1;
		}
		g[tr] = 0;
		for(int i = 1; i < tot; ++i) {
			int u = ord[i], p = par[u], DIS = g[u] = g[p] + 1;
			if(DIS < LEN) {
				++F[DIS];
			} else {
				F[LEN++] = 1;
			}
			++DIS;
			if(DIS < PLEN) {
				++PF[DIS];
			} else {
				PF[PLEN++] = 1;
			}
		}
		CLEN = min(LEN + LEN - 1, cnt - 2);
		if(CLEN <= 0)
			continue;
		polySquare(LEN, F, CLEN, CF);
		for(int i = 0, j = 2; i < CLEN; ++i, ++j)
			ans[j] -= CF[i];
	}
	CLEN = min(PLEN + PLEN - 1, cnt);
	polySquare(PLEN, PF, CLEN, CF);
	for(int i = 0; i < CLEN; ++i)
		ans[i] += CF[i];
	for(vector<int>::iterator it = e[rt].begin(); it != e[rt].end(); ++it)
		if(!ban[*it])
			solve(*it);
}
int main() {
	scanf("%d", &n);
	initFFT(n + 1);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	solve(0);
	DB res = 0;
	for(int i = 0; i < n; ++i)
		res += ans[i] / (i + 1.0);
	printf("%.4f\n", res);
	return 0;
}