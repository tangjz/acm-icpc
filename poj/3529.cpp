#include <cstdio>
typedef long long LL;
const int maxn = 21, maxd = maxn << 1 | 1, mod = (int)1e9 + 7;
int n, m, q, f[maxn][maxn][maxd], g[maxn][maxn], row[maxn][maxn], col[maxn][maxn];
int iact[maxd], pre[maxd], suf[maxd];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", g[i] + j);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", f[i][j] + 0);
	int upp = n + m - 2;
	iact[1] = 1;
	for(int i = 2; i <= upp; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	iact[0] = 1;
	for(int k = 1; k <= upp; ++k) {
		iact[k] = (LL)iact[k - 1] * iact[k] % mod;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j) {
				f[i][j][k] = f[i][j][k - 1];
				mod_inc(f[i][j][k], row[i][j] = j ? row[i][j - 1] : 0);
				mod_inc(f[i][j][k], col[i][j] = i ? col[i - 1][j] : 0);
				int tmp = (LL)f[i][j][k] * g[i][j] % mod;
				mod_inc(row[i][j], tmp);
				mod_inc(col[i][j], tmp);
			}
	}
	while(q--) {
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		int ans = 0, upp = (--x) + (--y), *F = f[x][y];
		if((--k) <= upp) {
			ans = F[k];
		} else {
			for(int i = 0; i <= upp; ++i)
				pre[i] = suf[i] = k - i;
			for(int i = 1; i <= upp; ++i)
				pre[i] = (LL)pre[i - 1] * pre[i] % mod;
			for(int i = upp - 1; i >= 0; --i)
				suf[i] = (LL)suf[i] * suf[i + 1] % mod;
			for(int i = 0; i <= upp; ++i) {
				int tmp = F[i];
				if(i > 0)
					tmp = (LL)tmp * iact[i] % mod * pre[i - 1] % mod;
				if(i < upp)
					tmp = (LL)tmp * iact[upp - i] % mod * suf[i + 1] % mod;
				if(tmp && (upp - i) & 1)
					tmp = mod - tmp;
				mod_inc(ans, tmp);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}