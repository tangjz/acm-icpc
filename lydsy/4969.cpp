#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxLen = 18, maxs = 1 << maxLen | 1, mod = 998244353, gen = 3, inv2 = (mod + 1) >> 1;
int n, inv[maxn], w[maxs << 1 | 1];
vector<int> f[maxn], g[maxn];
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
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
void solve(int L, int R) {
	if(L == R)
		return;
	int M = (L + R) >> 1;
	solve(L, M);
	solve(M + 1, R);
	int u = L, v = M + 1;
	polyMul(f[u], g[v], f[u]);
	polyMul(g[u], f[v], f[v]);
	int szL = f[u].size(), szR = f[v].size();
	if(szL < szR)
		f[u].resize(szR);
	for(int i = 0; i < szR; ++i)
		f[u][i] = mod_add(f[u][i], f[v][i]);
	polyMul(g[u], g[v], g[u]);
	vector<int>().swap(f[v]);
	vector<int>().swap(g[v]);
}
int main() {
	scanf("%d", &n);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	vector<int> a, b;
	a.reserve(n + 1);
	b.reserve(n + 1);
	for(int i = 0, x, y; i <= n; ++i) {
		scanf("%d", &x);
		y = i ? (LL)y * inv[i] % mod : 1;
		x = (LL)x * y % mod;
		a.push_back(x);
		b.push_back(y);
	}
	initNTT(n << 1 | 1);
	polyMul(a, b, a);
	a.resize(n + 1);
	for(int i = n, x, y; i >= 0; --i) {
		y = i < n ? (LL)y * inv[n - i] % mod : 1;
		x = (LL)a[i] * y % mod;
		if(x && (i & 1))
			x = mod - x;
		f[i].reserve(1);
		f[i].push_back(x);
		g[i].reserve(2);
		g[i].push_back(i ? mod - i : 0);
		g[i].push_back(1);
	}
	solve(0, n);
	for(int i = 0; i <= n; ++i)
		printf("%d%c", f[0][i], " \n"[i == n]);
	return 0;
}