#include <cstdio>
const int maxn = 601;
int n, m, q, f[maxn][maxn];
inline void upd(int &x, int y) {
	x > y && (x = y);
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			f[i][j] = f[i][j - 1] + i;
	while(q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		f[x][y] = 0;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			for(int k = 1; k < i; ++k)
				upd(f[i][j], f[k][j] + f[i - k][j]);
			for(int k = 1; k < j; ++k)
				upd(f[i][j], f[i][k] + f[i][j - k]);
		}
	printf("%d\n", f[n][m]);
	return 0;
}
