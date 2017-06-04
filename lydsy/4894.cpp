#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 301, mod = 1000000007;
int n, mat[maxn][maxn], ans;
char buf[maxn];
inline int mod_inv(int x, int m) {
	int y = m, u = 1, v = 0, r;
	while(y) {
		r = x / y;
		std::swap(x, y);
		y -= x * r;
		std::swap(u, v);
		v -= u * r;
	} // assert(x == 1);
	return u < 0 ? u + m : u;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf);
		for(int j = 0; j < n; ++j)
			if(buf[j] == '1') {
				++mat[j][j];
				--mat[i][j];
			}
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			for( ; mat[i][j] < 0; mat[i][j] += mod);
			for( ; mat[i][j] >= mod; mat[i][j] -= mod);
		}
	ans = 1;
	for(int i = 1; i < n; ++i) {
		int k = -1;
		for(int j = i; j < n; ++j)
			if(mat[j][i]) {
				k = j;
				break;
			}
		if(k == -1) {
			ans = 0;
			break;
		}
		if(i != k) {
			for(int j = i; j < n; ++j)
				std::swap(mat[i][j], mat[k][j]);
			ans = mod - ans;
		}
		ans = (LL)ans * mat[i][i] % mod;
		int inver = mod - mod_inv(mat[i][i], mod);
		for(int j = i + 1; j < n; ++j) {
			int d = (LL)mat[j][i] * inver % mod;
			for(k = i; k < n; ++k)
				mat[j][k] = (mat[j][k] + (LL)mat[i][k] * d) % mod;
		}
	}
	printf("%d\n", ans);
	return 0;
}
