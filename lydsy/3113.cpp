#include <cstdio>
typedef long long LL;
int n, m, p[9], e[9];
LL mod, ans;
inline LL mod_add(LL x, LL y, LL p) {
	return (x += y) >= p ? x - p : x;
}
inline LL mod_mul(LL x, LL y, LL p) {
	LL ret = x * y - (LL)((long double)x * y / p + 0.01) * p;
	return ret < 0 ? ret + p : ret;
}
struct Matrix {
	int r, c;
	LL num[3][3];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {r, t.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = mod_add(ret.num[i][k], mod_mul(num[i][j], t.num[j][k], mod), mod);
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
} A, B;
void dfs(int dep, int val, int phi) {
	if(dep == m) {
		B = A.pow(n / val);
		LL coeff = mod_add(B.num[1][0], B.num[2][0], mod);
		ans = mod_add(ans, mod_mul(coeff, phi, mod), mod);
		return;
	}
	for(int i = 0; i <= e[dep]; ++i) {
		dfs(dep + 1, val, phi);
		val *= p[dep];
		phi *= p[dep] - !i;
	}
}
int main() {
	while(scanf("%d%lld", &n, &mod) == 2) {
		mod *= n;
		int tmp = n;
		m = 0;
		for(int i = 2; (LL)i * i <= tmp; ++i)
			if(tmp % i == 0) {
				for(e[m] = 1, tmp /= i; tmp % i == 0; ++e[m], tmp /= i);
				p[m++] = i;
			}
		if(tmp > 1) {
			p[m] = tmp;
			e[m++] = 1;
		}
		A.r = A.c = 3;
		A.num[0][0] = A.num[0][2] = A.num[1][2] = A.num[2][0] = 0;
		A.num[0][1] = mod - 1;
		A.num[1][0] = A.num[2][2] = 1;
		A.num[1][1] = 3;
		A.num[2][1] = 2;
		ans = 0;
		dfs(0, 1, 1);
		printf("%d\n", (int)(ans / n));
	}
	return 0;
}
