#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 101;
int n, m, mod, mat[5][maxn][maxn];
void mat_add(int (*lft)[maxn], int (*rht)[maxn], int (*res)[maxn]) {
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			(res[i][j] = lft[i][j] + rht[i][j]) >= mod && (res[i][j] -= mod);
}
void mat_mul(int (*lft)[maxn], int (*rht)[maxn], int (*res)[maxn]) {
	static LL tmp[maxn][maxn];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			tmp[i][j] = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) if(lft[i][j])
			for(int k = 0; k < n; ++k) if(rht[j][k])
				if((tmp[i][k] += (LL)lft[i][j] * rht[j][k]) < 0)
					tmp[i][k] = (ULL)tmp[i][k] % mod;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			res[i][j] = tmp[i][j] < mod ? tmp[i][j] : tmp[i][j] % mod;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		static char buf[maxn];
		scanf("%s", buf);
		for(int j = 0; j < n; ++j) {
			mat[0][i][j] = buf[j] == 'Y';
			mat[1][i][j] = mat[2][i][j] = i == j;
		}
	}
	scanf("%d%d", &m, &mod);
	for(int i = 0; m > 0; m >>= 1, ++i) {
		if(i) {
			mat_mul(mat[0], mat[1], mat[3]);
			mat_add(mat[1], mat[3], mat[1]);
			mat_mul(mat[0], mat[0], mat[0]);
		}
		if(m & 1) {
			mat_mul(mat[2], mat[1], mat[3]);
			mat_add(mat[4], mat[3], mat[4]);
			mat_mul(mat[2], mat[0], mat[2]);
		}
	}
	LL ans = 0;
	for(int i = 0; i < n; ++i)
		ans += mat[4][i][i] - 1;
	(ans %= mod) < 0 && (ans += mod);
	printf("%d\n", (int)ans);
	return 0;
}