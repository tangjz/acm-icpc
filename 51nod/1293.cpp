#include <stdio.h>
typedef long long LL;
const int maxn = 1001;
int n, m, a[maxn][maxn];
LL f[maxn][maxn], g[maxn][maxn];
int main() {
	scanf("%d%d%lld", &m, &n, &f[0][0]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			int typ;
			scanf("%d", &typ);
			if(typ == 0) {
				f[i + 1][j] += f[i][j];
				g[i][j + 1] += g[i][j];
			} else {
				LL ctr = f[i][j] + g[i][j];
				if(typ == -1) {
					f[i + 1][j] += (ctr + 1) >> 1;
					g[i][j + 1] += ctr >> 1;
				} else {
					f[i + 1][j] += ctr >> 1;
					g[i][j + 1] += (ctr + 1) >> 1;
				}
			}
		}
	printf("%lld\n", f[n][m - 1]);
	return 0;
}
