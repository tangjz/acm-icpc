#include <cstdio>
typedef long long LL;
int t;
LL p, m, x, q, n, phi;
inline LL mod_add(LL x, LL y, LL p) {
	return (x += y) >= p ? x - p : x;
}
inline LL mod_sub(LL x, LL y, LL p) {
	return (x += y) >= p ? x - p : x;
}
inline LL mod_mul(LL x, LL y, LL p) {
	LL ret = x * y - (LL)((long double)x * y / p + 0.01) * p;
	return ret < 0 ? ret + p : ret;
}
inline LL mod_pow(LL x, LL k, LL p) {
	LL ret = 1;
	for( ; k > 0; k >>= 1, x = mod_mul(x, x, p))
		(k & 1) && (ret = mod_mul(ret, x, p));
	return ret;
}
struct Matrix {
	int r, c;
	LL num[3][3];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {r, t.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = mod_add(ret.num[i][k], mod_mul(num[i][j], t.num[j][k], phi), phi);
		return ret;
	}
	Matrix pow(LL k) const {
		Matrix ret = {r, r}, tmp = *this;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		for( ; k > 0; k >>= 1, tmp = tmp * tmp)
			(k & 1) && (ret = ret * tmp, 1);
		return ret;
	}
} A;
int main() {
	scanf("%d%lld", &t, &p);
	LL tmp = p;
	phi = p;
	for(int i = 2; (LL)i * i <= tmp; ++i)
		if(tmp % i == 0)
			for(phi -= phi / i, tmp /= i; tmp % i == 0; tmp /= i);
	if(tmp > 1)
		phi -= phi / tmp;
	while(t--) {
		scanf("%lld%lld%lld%lld", &m, &x, &q, &n);
		tmp = mod_pow(x % p, mod_pow(m % phi, n, phi), p);
		A.r = A.c = 3;
		A.num[0][0] = m % phi;
		A.num[1][0] = A.num[1][1] = A.num[2][0] = A.num[2][1] = A.num[2][2] = 1;
		A = A.pow(n);
		tmp = mod_mul(tmp, mod_pow(q % p, A.num[2][0], p), p);
		printf("%lld\n", tmp);
	}
	return 0;
}
