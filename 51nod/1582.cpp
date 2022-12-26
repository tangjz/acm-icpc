#include <stdio.h>
typedef long long LL;
const int maxn = 101, mod = 1000000007;
void mod_inc_mul(int &x, int y, int z) {
	x = (x + (LL)y * z) % mod;
}
struct Matrix {
	int r, c, num[maxn][maxn];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {r, t.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					mod_inc_mul(ret.num[i][k], num[i][j], t.num[j][k]);
		return ret;
	}
	Matrix pow(int k) const {
		Matrix ret = {r, r}, tmp = *this;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		for( ; k > 0; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
} A;
int n, m, d;
int main() {
	A.r = A.c = 101;
	for(int i = 0; i < 99; ++i)
		A.num[i + 1][i] = 1;
	A.num[100][99] = A.num[100][100] = 1;
	scanf("%d%d", &n, &m);
	while(n--) {
		scanf("%d", &d);
		++A.num[100 - d][99];
	}
	A = A.pow(m);
	d = A.num[99][99] + A.num[100][99];
	printf("%d\n", d < mod ? d : d - mod);
	return 0;
}
