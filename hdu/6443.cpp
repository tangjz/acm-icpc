#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 3, maxLen = 18, maxm = 1 << maxLen | 1, mod = 998244353, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxm];
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : x - mod;
}
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}
inline int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
void NTT(int len, int x[], int flag) {
	static int bitLen = 0, ivs = 1, bitRev[maxm] = {};
	if(len != (1 << bitLen)) {
		for(bitLen = 0, ivs = 1; 1 << bitLen < len; ++bitLen, ivs = (LL)ivs * inv2 % mod);
		for(int i = 1; i < len; ++i)
		    bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
	}
	for(int i = 1; i < len; ++i)
		if(i < bitRev[i])
			swap(x[i], x[bitRev[i]]);
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d << 1)
			for(int k = 0, *X = x + j; k < d; ++k) {
				int tp = (LL)w[k << (maxLen - i)] * X[k + d] % mod;
				X[d + k] = mod_sub(X[k], tp);
				X[k] = mod_add(X[k], tp);
			}
	if(flag != -1) return;
	reverse(x + 1, x + len);
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * ivs % mod;
}
int fact[maxn << 1 | 1], iact[maxn];
int t, n, m, e[maxn], c[maxn];
int f[maxm], g[maxm];
int main() {
	w[0] = 1;
	w[1] = mod_pow(gen, (mod - 1) >> maxLen);
	for(int i = 2; i < maxm; ++i)
		w[i] = (LL)w[i - 1] * w[1] % mod;
	fact[0] = 1;
	for(int i = 1; i < maxn << 1; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &m);
		n = 0;
		bool chk = 0;
		for(int i = 0, p; i < m; ++i) {
			scanf("%d%d", &p, e + i);
			if(p == 2) {
				chk = 1;
				++e[i];
			}
			n += e[i];
		}
		if(!chk) {
			e[m++] = 1;
			++n;
		}
		sort(e, e + m);
		int tp = 0;
		for(int i = 0; i < m; ++i)
			if(!tp || e[tp - 1] < e[i]) {
				e[tp] = e[i];
				c[tp++] = 1;
			} else {
				++c[tp - 1];
			}
		f[0] = 0;
		for(int i = 1; i <= n; ++i) {
			f[i] = (LL)iact[i] * mod_pow(iact[i - 1], m) % mod;
			for(int j = 0; j < tp; ++j)
				f[i] = (LL)f[i] * mod_pow((LL)fact[e[j] + i - 1] * iact[e[j]] % mod, c[j]) % mod;
		}
		int len;
		for(len = 1; len <= (n << 1); len <<= 1);
		memset(f + n + 1, 0, (len - n - 1) * sizeof(int));
		NTT(len, f, 1);
		for(int i = 0; i <= n; ++i)
			g[i] = i & 1 ? mod - iact[i] : iact[i];
		memset(g + n + 1, 0, (len - n - 1) * sizeof(int));
		NTT(len, g, 1);
		for(int i = 0; i < len; ++i)
			f[i] = (LL)f[i] * g[i] % mod;
		NTT(len, f, -1);
		int ans = 0;
		for(int i = 1; i <= n; ++i) {
			f[i] = (LL)f[i] * fact[i] % mod;
			ans = (ans + (LL)f[i] * (f[i - 1] + f[i])) % mod;
		}
		ans = mod_add(ans, ans);
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
