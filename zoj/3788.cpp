#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1001, mod = 5767169;
int inv[mod], fact[mod], iact[mod];
int C(int n, int m) {
	if(n < m)
		return 0;
	if(n < mod)
		return (LL)fact[n] * iact[n - m] % mod * iact[m] % mod;
	return (LL)C(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
struct Poly {
	int len, term[maxn << 1 | 1];
	Poly operator * (const Poly &t) const {
		Poly ret = {len + t.len - 1};
		for(int i = 0; i < len; ++i)
			for(int j = 0; j < t.len; ++j)
				ret.term[i + j] = (ret.term[i + j] + (LL)term[i] * t.term[j]) % mod;
		for( ; ret.len > 0 && !ret.term[ret.len - 1]; --ret.len);
		return ret;
	}
	Poly operator % (const Poly &t) const {
		Poly ret = *this;
		for(int i = ret.len; i >= t.len; --i) {
			int coeff = (LL)ret.term[i - 1] * inv[t.term[t.len - 1]] % mod;
			for(int j = 1; j <= t.len; ++j)
				if((ret.term[i - j] = (ret.term[i - j] - (LL)coeff * t.term[t.len - j]) % mod) < 0)
					ret.term[i - j] += mod;
		}
		for( ; ret.len > 0 && !ret.term[ret.len - 1]; --ret.len);
		return ret;
	}
} A, B, M;
int main() {
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < mod; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * inv[i] % mod;
	}
	int p, q, a, b, n;
	while(scanf("%d%d%d%d%d", &p, &q, &a, &b, &n) == 5) {
		int bound = (int)ceil(pow(n, 1 / 3.0));
		if(a < b) {
			swap(p, q);
			swap(a, b);
		}
		int ans = 0;
		p %= mod;
		q %= mod;
		if(a <= bound) {
			A = (Poly){1};
			B = (Poly){2};
			M = (Poly){a + 1};
			p && (M.term[0] = mod - p);
			q && (M.term[a - b] = mod - q);
			A.term[0] = B.term[1] = M.term[a] = 1;
			for(n += a - 1; n > 0; n >>= 1, B = B * B % M)
				if(n & 1)
					A = A * B % M;
			ans = A.len == a ? A.term[a - 1] : 0;
		} else {
			for(int i = 0; i * a <= n; ++i) {
				int rem = n - i * a;
				if(rem % b > 0)
					continue;
				int j = rem / b;
				ans = (ans + (LL)C(i + j, j) * mod_pow(p, i) % mod * mod_pow(q, j)) % mod;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
