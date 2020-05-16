#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi = acos(-1.0);
const int maxm = 101, maxv = 10001, maxl = 101, maxLen = 15, maxk = 1 << maxLen | 1;
const int mod = (int)1e9 + 7, sp = 15, msk = 32767, INF = 0x3f3f3f3f;
struct Complex {
	DB r, i;
	Complex() {}
	Complex(DB r, DB i) : r(r), i(i) {}
	Complex operator + (Complex const &t) const {
		return Complex(r + t.r, i + t.i);
	} Complex operator - (Complex const &t) const {
		return Complex(r - t.r, i - t.i);
	} Complex operator * (Complex const &t) const {
		return Complex(r * t.r - i * t.i, r * t.i + i * t.r);
	} Complex conj() const {
		return Complex(r, -i);
	}
} w[maxk];
int inv[maxv], t, n, m, p, c[maxm], coeff[2][maxv];
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
void FFT(int n, Complex a[], int flag) {
	static int bitLen = 0, bitRev[maxk] = {};
	if(n != (1 << bitLen)) {
		for(bitLen = 0; 1 << bitLen < n; ++bitLen);
		for(int i = 1; i < n; ++i)
			bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
	}
	for(int i = 0; i < n; ++i)
		if(i < bitRev[i])
			swap(a[i], a[bitRev[i]]);
	for(int i = 1, d = 1; d < n; ++i, d <<= 1)
		for(int j = 0; j < n; j += d << 1)
			for(int k = 0; k < d; ++k) {
				Complex &AL = a[j + k], &AH = a[j + k + d];
				Complex TP = w[k << (maxLen - i)] * AH;
				AH = AL - TP, AL = AL + TP;
			}
	if(flag != -1)
		return;
	reverse(a + 1, a + n);
	for(int i = 0; i < n; ++i) {
		a[i].r /= n;
		a[i].i /= n;
	}
}
void solve(int idx, int n) { // (100-p + p x)^n mod (x^c[0] - 1)
	if(n < c[0]) {
		int prd = mod_pow(100 - p, n), adt = (LL)p * inv[100 - p] % mod;
		for(int i = 0; i <= n; ++i) {
			coeff[idx][i] = prd;
			prd = (LL)prd * (n - i) % mod * inv[i + 1] % mod * adt % mod;
		}
		memset(coeff[idx] + n + 1, 0, (c[0] - n - 1) * sizeof(int));
	} else if(n & 1) {
		solve(idx ^ 1, n - 1);
		for(int i = 0, j = c[0] - 1; i < c[0]; j = i++)
			coeff[idx][i] = ((LL)(100 - p) * coeff[idx ^ 1][i] + (LL)p * coeff[idx ^ 1][j]) % mod;
	} else {
		solve(idx ^ 1, n >> 1);
		int len;
		static Complex A[maxk], C[maxk], D[maxk];
		for(len = 1; len < (c[0] << 1); len <<= 1);
		for(int i = 0; i < len; ++i)
			A[i] = i < c[0] ? Complex(coeff[idx ^ 1][i] & msk, coeff[idx ^ 1][i] >> sp) : Complex(0, 0);
		FFT(len, A, 1);
		Complex trL(0.5, 0), trH(0, -0.5), tr(0, 1);
		for(int i = 0; i < len; ++i) {
			int j = (len - i) & (len - 1);
			Complex AL = (A[i] + A[j].conj()) * trL;
			Complex AH = (A[i] - A[j].conj()) * trH;
			C[i] = AL * (AL + AH * tr);
			D[i] = AH * (AL + AH * tr);
		}
		FFT(len, C, -1);
		FFT(len, D, -1);
		for(int i = 0; i < c[0]; ++i) {
			int v11 = (LL)(C[i].r + 0.5) % mod, v12 = (LL)(C[i].i + 0.5) % mod;
			int v21 = (LL)(D[i].r + 0.5) % mod, v22 = (LL)(D[i].i + 0.5) % mod;
			coeff[idx][i] = (((((LL)v22 << sp) + v12 + v21) << sp) + v11) % mod;
		}
		for(int i = c[0]; i < (c[0] << 1); ++i) {
			int v11 = (LL)(C[i].r + 0.5) % mod, v12 = (LL)(C[i].i + 0.5) % mod;
			int v21 = (LL)(D[i].r + 0.5) % mod, v22 = (LL)(D[i].i + 0.5) % mod;
			(coeff[idx][i - c[0]] += (((((LL)v22 << sp) + v12 + v21) << sp) + v11) % mod) >= mod && (coeff[idx][i - c[0]] -= mod);
		}
	}
}
int solve1() {
	if(p == 100)
		return n % c[0] ? (LL)(c[0] - n % c[0]) * mod_pow(100, n) % mod : 0;
	int ret = 0;
	solve(0, n);
	for(int i = 1; i < c[0]; ++i)
		ret = (ret + (LL)(c[0] - i) * coeff[0][i]) % mod;
	return ret;
}
int solve2() {
	static int low[maxl];
	static bool vis[maxv];
	priority_queue<pair<int, int> > Q;
	memset(low, 0x3f, c[0] * sizeof(int));
	memset(vis, 0, c[0] * sizeof(bool));
	low[0] = 0;
	Q.push(make_pair(-low[0], 0));
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(int i = 1; i < m; ++i) {
			int v = (u + c[i]) % c[0], tp = low[u] + c[i];
			if(tp < low[v])
				Q.push(make_pair(-(low[v] = tp), v));
		}
	}
	if(p == 100) {
		int rem = n;
		for(int i = 0; i < c[0]; ++i)
			if(low[i] < INF) {
				int j = low[i] + (low[i] < n ? ((n - low[i] - 1) / c[0] + 1) * c[0] : 0);
				rem = min(rem, j - n);
			}
		return (LL)rem * mod_pow(100, n) % mod;
	}
	int ret = 0, all = c[m - 2] * c[m - 1], las = all - 1;
	static int rem[maxv];
	solve(0, n);
	memset(vis, 0, all * sizeof(bool));
	for(int i = 0; i < c[0]; ++i) {
		for(int j = low[i]; j < all; j += c[0])
			vis[j] = 1;
		if(low[las % c[0]] == INF)
			++las;
	}
	for(int i = all - 1; i >= 0; --i) {
		if(vis[i])
			las = i;
		rem[i] = las - i;
	}
	int prd = mod_pow(100 - p, n), adt = (LL)p * inv[100 - p] % mod;
	for(int i = 0; i < all && i <= n; ++i) {
		(coeff[0][i % c[0]] -= prd) < 0 && (coeff[0][i % c[0]] += mod);
		ret = (ret + (LL)rem[i] * prd) % mod;
		prd = (LL)prd * (n - i) % mod * inv[i + 1] % mod * adt % mod;
	}
	las = 0;
	for(int i = c[0] - 1; i >= 0; --i) {
		if(low[i] != INF)
			las = i;
		int rem = las < i ? las - i + c[0] : las - i;
		ret = (ret + (LL)rem * coeff[0][i]) % mod;
	}
	return ret;
}
int main() {
	inv[1] = 1;
	for(int i = 2; i < maxv; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i) {
		int j = i, k = ilim >> 1; // 2 pi / ilim
		for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
		w[i] = Complex(cos(pi / k * j), sin(pi / k * j));
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d%d", &n, &m, &p);
		for(int i = 0; i < m; ++i)
			scanf("%d", c + i);
		sort(c, c + m);
		printf("Case #%d: %d\n", Case, p ? (m == 1 ? solve1() : solve2()) : 0);
	}
	return 0;
}
