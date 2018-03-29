#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
const LL BLEN = 29, BMSK = (1LL << BLEN) - 1;
LL mod;
char buf[maxn];
inline LL mod_add(LL x, LL y) {
	return (x += y) < mod ? x : x - mod;
}
inline LL mod_sub(LL x, LL y) {
	return (x -= y) < 0 ? x + mod : x;
}
inline LL mod_mul(LL x, LL y) {
	if(y >> BLEN) {
		LL ret = x * (y & BMSK) % mod;
		y >>= BLEN;
		x = (x << BLEN) % mod;
		return (ret + x * y) % mod;
	}
	return x * y % mod;
}
inline LL mod_pow(LL x, LL k) {
	LL ret = 1 % mod;
	for( ; k > 0; k >>= 1, x = mod_mul(x, x))
		(k & 1) && (ret = mod_mul(ret, x));
	return ret;
}
struct Matrix {
	LL num[5][5];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j)
				for(int k = 0; k < 4; ++k)
					ret.num[i][k] = mod_add(ret.num[i][k], mod_mul(num[i][j], t.num[j][k]));
		return ret;
	}
	Matrix pow(LL k) const {
		Matrix ret = {}, tmp = *this;
		for(int i = 0; i < 4; ++i)
			ret.num[i][i] = 1 % mod;
		for( ; k > 0; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
} A;
int main() {
	int n, m, len = 0;
	scanf("%s%d%lld", buf, &m, &mod);
	n = strlen(buf);
	mod *= 9;
	LL pw = 1 % mod, s0 = 0, s1 = 0, s2 = 0, s3 = 0;
	for(int i = n - 1; i >= 0; --i, ++len, pw = mod_mul(pw, 10)) {
		int dig = (buf[i] - '0') % mod;
		s0 = mod_add(s0, dig);
		s1 = mod_add(s1, mod_mul(len, dig));
		s2 = mod_add(s2, mod_mul(pw, dig));
		s3 = mod_add(s3, mod_mul(len, mod_mul(pw, dig)));
	}
	LL c0 = m % mod, c1 = c0 * (c0 + 1LL) / 2 % mod, c2, c3;
	A.num[0][0] = A.num[1][1] = pw;
	A.num[0][1] = pw ? mod - pw : 0;
	A.num[0][2] = A.num[1][3] = A.num[2][2] = A.num[3][3] = 1 % mod;
	A = A.pow(m);
	c2 = mod_add(A.num[0][2], mod_mul(m, A.num[1][2]));
	c3 = mod_add(A.num[0][3], mod_mul(m, A.num[1][3]));
	LL ans = mod_add(mod_sub(mod_sub(mod_mul(10, mod_mul(len, mod_mul(c3, s2))), mod_mul(10, mod_mul(c2, s3))), mod_mul(len, mod_mul(c1, s0))), mod_mul(c0, s1));
	printf("%d\n", (int)(ans / 9));
	return 0;
}
