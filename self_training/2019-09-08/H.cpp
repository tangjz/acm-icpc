#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef LL Matrix[2][2];
const int maxd = 2, BLEN = 15, BMSK = (1 << BLEN) - 1, mod = 998244353, per = (mod - 1) >> 1;
inline int mod_fix(LL &x) { // assert(x >= 0);
	return x < mod ? x : (x %= mod);
}
inline LL mod_inc_mul(LL &x, int y, int z) {
	y && z && (x += (LL)y * z) < 0 && (x = (ULL)x % mod);
}
inline void mat_mul(Matrix &A, Matrix &B, Matrix &C) { // A = B * C
	A[0][0] = A[0][1] = A[1][0] = A[1][1] = 0;
	mod_inc_mul(A[0][0], mod_fix(B[0][0]), mod_fix(C[0][0]));
	mod_inc_mul(A[0][1], mod_fix(B[0][0]), mod_fix(C[0][1]));
	mod_inc_mul(A[0][0], mod_fix(B[0][1]), mod_fix(C[1][0]));
	mod_inc_mul(A[0][1], mod_fix(B[0][1]), mod_fix(C[1][1]));
	mod_inc_mul(A[1][0], mod_fix(B[1][0]), mod_fix(C[0][0]));
	mod_inc_mul(A[1][1], mod_fix(B[1][0]), mod_fix(C[0][1]));
	mod_inc_mul(A[1][0], mod_fix(B[1][1]), mod_fix(C[1][0]));
	mod_inc_mul(A[1][1], mod_fix(B[1][1]), mod_fix(C[1][1]));
}
Matrix f[maxd][BMSK + 2], g[2];
int main() {
	for(int i = 0; i < maxd; ++i) {
		{
			Matrix &cur = f[i][0];
			cur[0][0] = cur[1][1] = 1;
			cur[0][1] = cur[1][0] = 0;
		}
		if(i) {
			mat_mul(f[i][1], f[i - 1][1], f[i - 1][BMSK]);
		} else {
			Matrix &cur = f[i][1];
			cur[0][0] = 0;
			cur[0][1] = 2;
			cur[1][0] = 1;
			cur[1][1] = 3;
		}
		for(int j = 2; j <= BMSK; ++j)
			mat_mul(f[i][j], f[i][1], f[i][j - 1]);
	}
	int q, ans = 0, cur = 0, pre = 1;
	LL n, tp;
	scanf("%d%lld", &q, &n);
	for(int i = 0; i < q; ++i) {
		g[cur][0][0] = g[cur][1][1] = 1;
		g[cur][0][1] = g[cur][1][0] = 0;
		tp = n % per;
		for(int j = 0; tp > 0; ++j, tp >>= BLEN)
			if(tp & BMSK) {
				swap(cur, pre);
				mat_mul(g[cur], g[pre], f[j][tp & BMSK]);
			}
		int res = mod_fix(g[cur][1][0]);
		ans ^= res;
		n ^= (LL)res * res;
	}
	printf("%d\n", ans);
	return 0;
}