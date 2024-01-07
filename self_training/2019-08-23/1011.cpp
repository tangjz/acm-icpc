#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = 998244353;
int mod_pow(int x, int k, int m) {
	int ret = m > 1 ? 1 : 0;
	for( ; k > 0; k >>= 1, x = (LL)x * x % m)
		if(k & 1)
			ret = (LL)ret * x % m;
	return ret;
}
pair<int, int> solve(int n) {
	static const int mod = 1 << 23;
	static bool enabled = 0;
	static int fact[mod + 1];
	if(!enabled) {
		fact[0] = 1;
		for(int i = 1; i < mod; ++i) {
			fact[i] = fact[i - 1];
			if(i & 1)
				fact[i] = (LL)fact[i - 1] * i % mod;
		}
		enabled = 1;
	}
	if(!n)
		return make_pair(1, 0);
	pair<int, int> ret = solve(n >> 1);
	ret.first = (LL)ret.first * mod_pow(fact[mod - 1], n / mod, mod) % mod * fact[n % mod] % mod;
	ret.second += n >> 1;
	return ret;
}
int solve(int n, int x, int y) {
	// n! / x! / y! / (n - x - y)!
	pair<int, int> t1 = solve(n), t2 = solve(x), t3 = solve(y), t4 = solve(n - x - y);
	int mod = 1 << 23, res = (LL)t1.first * mod_pow((LL)t2.first * t3.first % mod * t4.first % mod, (mod >> 1) - 1, mod) % mod;
	for(int i = min(t1.second - t2.second - t3.second - t4.second, 23); i > 0; --i)
		(res <<= 1) >= mod && (res -= mod);
	static bool enabled = 0;
	static int c7[7][7], c17[17][17];
	if(!enabled) {
		for(int i = 0; i < 7; ++i)
			c7[0][i] = i ? 0 : 1;
		for(int i = 1; i < 7; ++i)
			for(int j = 0; j < 7; ++j)
				c7[i][j] = (c7[i - 1][j] + (j ? c7[i - 1][j - 1] : 0)) % 7;
		for(int i = 0; i < 17; ++i)
			c17[0][i] = i ? 0 : 1;
		for(int i = 1; i < 17; ++i)
			for(int j = 0; j < 17; ++j)
				c17[i][j] = (c17[i - 1][j] + (j ? c17[i - 1][j - 1] : 0)) % 17;
		enabled = 1;
	}
	int r7 = 1;
	for(int u = n, v = x + y, w = x; u > 0; u /= 7, v /= 7, w /= 7) {
		int A = u % 7, B = v % 7, C = w % 7;
		r7 = r7 * c7[A][B] * c7[B][C] % 7;
	}
	for( ; res % 7 != r7; res += mod);
	mod *= 7;
	int r17 = 1;
	for(int u = n, v = x + y, w = x; u > 0; u /= 17, v /= 17, w /= 17) {
		int A = u % 17, B = v % 17, C = w % 17;
		r17 = r17 * c17[A][B] * c17[B][C] % 17;
	}
	for( ; res % 17 != r17; res += mod);
	mod *= 17;
	return res;
}
int t1, t2, p, q, n, m, x, y, v, ans;
int main() {
	while(scanf("%d%d%d%d%d%d", &t1, &t2, &p, &q, &n, &m) == 6) {
		ans = 1;
		while(m--) {
			scanf("%d%d%d", &x, &y, &v);
			if(x % p > 0 || y % q > 0 || v <= 1)
				continue;
			x /= p;
			y /= q;
			if(x + y > n)
				continue;
			int pw = (LL)solve(n, x, y) * mod_pow(t1, x, mod - 1) % (mod - 1) * mod_pow(t2, y, mod - 1) % (mod - 1);
			ans = (LL)ans * mod_pow(v, pw, mod) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
