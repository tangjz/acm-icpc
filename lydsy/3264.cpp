#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = 301, maxl = 1801;
const ULL INF = maxn + maxn;
int phi[maxn], fib_len[maxn], fib_low[maxn], fib[maxn][maxl];
inline ULL mod_add(ULL x, ULL y, ULL p) {
	x = x < p ? x : x % p;
	y = y < p ? y : y % p;
	return x < p - y ? x + y : x - (p - y);
}
inline ULL mod_sub(ULL x, ULL y, ULL p) {
	x = x < p ? x : x % p;
	y = y < p ? y : y % p;
	return x < y ? x + (p - y) : x - y;
}
inline ULL mod_mul(ULL x, ULL y, ULL p) {
	x = x < p ? x : x % p;
	y = y < p ? y : y % p;
	ULL ret = 0;
	for( ; y > 0; y >>= 1, x = mod_add(x, x, p))
		(y & 1) && (ret = mod_add(ret, x, p));
	return ret;
}
inline ULL mod_sqr(ULL x, ULL p) {
	return mod_mul(x, x, p);
}
inline ULL mod_pow(ULL x, ULL k, ULL p) {
	ULL ret = 1 < p ? 1 : 1 % p;
	x = x < p ? x : x % p;
	for( ; k > 0; k >>= 1, x = mod_mul(x, x, p))
		(k & 1) && (ret = mod_mul(ret, x, p));
	return ret;
}
inline ULL int_pow(ULL x, ULL k) {
	ULL ret = 1;
	for( ; k > 0; k >>= 1, x = x * x)
		(k & 1) && (ret = ret * x);
	return ret;
}
ULL calc_h(ULL x, ULL y, ULL k, int p) {
	bool chk = 1;
	if(pow(x, y) < INF) {
		ULL z = int_pow(x, y);
		if(z < (ULL)fib_low[phi[p]] && pow(fib[phi[p]][z], k - 1) < INF && int_pow(fib[phi[p]][x], k - 1) < (ULL)phi[p])
			chk = 0;
	}
	return mod_pow(fib[p][mod_pow(x, y, fib_len[p])], mod_pow(fib[phi[p]][mod_pow(x, y, fib_len[phi[p]])], k - 1, phi[p]) + chk * phi[p], p);
}
int Mod;
struct Matrix {
	ULL num[2][2];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				for(int k = 0; k < 2; ++k)
					ret.num[i][k] = mod_add(ret.num[i][k], mod_mul(num[i][j], t.num[j][k], Mod), Mod);
		return ret;
	}
	Matrix pow(ULL k) const {
		Matrix ret = {}, tmp = *this;
		for(int i = 0; i < 2; ++i)
			ret.num[i][i] = 1 < Mod ? 1 : 1 % Mod;
		for( ; k > 0; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
} A;
ULL calc_g(ULL a, ULL b, ULL n, ULL p) {
	Mod = p - 1;
	A = (Matrix){{{0, 1}, {1, 1}}};
	n = A.pow(n + 1).num[0][1];
	Mod = p;
	ULL u = mod_mul(2, mod_add(a, b, p), p), v = mod_sub(0, mod_sqr(mod_sub(a, b, p), p), p);
	A = (Matrix){{{0, v}, {1 < Mod ? 1 : 1 % Mod, u}}};
	A = A.pow(n);
	return mod_mul(4, mod_add(mod_mul(2, A.num[0][0], p), mod_mul(u, A.num[1][0], p), p), p);
}
int main() {
	for(int i = 1; i < maxn; ++i) {
		phi[i] += i;
		for(int j = i + i; j < maxn; j += i)
			phi[j] -= phi[i];
		int v1 = 0, v2 = 1 % i;
		do {
			fib[i][fib_len[i]++] = v1;
			(v1 += v2) >= i && (v1 -= i);
			swap(v1, v2);
		} while(!(v1 == 0 && v2 == 1 % i));
		int u1 = 0, u2 = 1;
		fib_low[i] = fib_len[i];
		for(int j = 0; j < fib_len[i]; ++j) {
			if(u1 != fib[i][j]) {
				fib_low[i] = j;
				break;
			}
			u1 += u2;
			swap(u1, u2);
		}
	}
	ULL a, b, n, p, c, d, m, q, M;
	while(scanf("%llu%llu%llu%llu%llu%llu%llu%llu%llu", &a, &b, &n, &p, &c, &d, &m, &q, &M) == 9)
		printf("%llu\n", mod_pow(a, (p - 1) >> 1, p) != 1 || mod_pow(b, (p - 1) >> 1, p) != 1 ? 0 : mod_sqr(mod_mul(calc_h(c, d, m, q), calc_g(a, b, n, p), M), M));
	return 0;
}
