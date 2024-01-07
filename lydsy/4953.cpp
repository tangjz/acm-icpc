#include <cstdio>
typedef long long LL;
const int maxn = 256;
int n, m, sqr[maxn + 1], cur, pre = 1;
LL c[3][maxn + 1], f[2][maxn + 1], ans;
inline void upd(LL &x, LL y) {
	x > y && (x = y);
}
int main() {
	for(int i = 0; i < maxn; ++i)
		sqr[i] = i * i;
	scanf("%d%d", &n, &m);
	while(n--) {
		int r, p;
		scanf("%d%d", &r, &p);
		c[0][r] += p;
		c[1][r] += (LL)r * p;
		c[2][r] += (LL)sqr[r] * p;
	}
	for(int i = 1; i < maxn; ++i) {
		c[0][i] += c[0][i - 1];
		c[1][i] += c[1][i - 1];
		c[2][i] += c[2][i - 1];
	}
	for(int i = 0; i < maxn; ++i)
		f[cur][i] = c[0][i] * (LL)sqr[i] - c[1][i] * (LL)(i << 1) + c[2][i];
	for(int i = 1; i < m; ++i) {
		cur ^= 1;
		pre ^= 1;
		for(int j = 0; j < maxn; ++j) {
			f[cur][j] = f[pre][j];
			for(int k = 0; k < j; ++k) { // (k, j]
				int mid = (j + k) >> 1; // (k, mid] (mid, j]
				upd(f[cur][j], f[pre][k]
				+ (c[0][mid] - c[0][k]) * (LL)sqr[k] - (c[1][mid] - c[1][k]) * (LL)(k << 1) + (c[2][mid] - c[2][k])
				+ (c[0][j] - c[0][mid]) * (LL)sqr[j] - (c[1][j] - c[1][mid]) * (LL)(j << 1) + (c[2][j] - c[2][mid]));
			}
		}
	}
	ans = f[cur][maxn - 1];
	for(int i = 0; i < maxn - 1; ++i)
		upd(ans, f[cur][i] + (c[0][maxn - 1] - c[0][i]) * (LL)sqr[i] - (c[1][maxn - 1] - c[1][i]) * (LL)(i << 1) + (c[2][maxn - 1] - c[2][i]));
	printf("%lld\n", ans);
	return 0;
}
