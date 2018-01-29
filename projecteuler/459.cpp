#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, maxm = 1 << 11 | 1, maxd = 1 << 8 | 1;
int c[maxd][maxd];
int calc(int x, int y) {
	assert(x < 1 << 16 && y < 1 << 16);
	int xL = x & 255, xH = x >> 8;
	int yL = y & 255, yH = y >> 8;
	return ((c[xH][yH] ^ c[xH][yL] ^ c[xL][yH]) << 8) | (c[128][c[xH][yH]] ^ c[xL][yL]);
}
int f[maxn], sf[maxn], cf[maxm];
int g[maxn], sg[maxn], cg[maxm];
bool vis[maxm];
int main() {
	c[1][1] = 1;
	for(int p = 1, q = 2; p < 8; p = q, q <<= 1) {
		int msk = (1 << p) - 1, half = 1 << (p - 1);
		for(int i = 0; i < 1 << q; ++i) {
			int iL = i & msk, iH = i >> p;
			for(int j = 0; j < 1 << q; ++j) {
				int jL = j & msk, jH = j >> p;
				if(iH || jH)
					c[i][j] = ((c[iH][jH] ^ c[iH][jL] ^ c[iL][jH]) << p) | (c[half][c[iH][jH]] ^ c[iL][jL]);
			}
		}
	}
	int n;
	while(scanf("%d", &n) == 1) {
		int m, mx = 0;
		for(m = 1; m * m <= n; m <<= 1);
		for( ; m * (m + 1) / 2 <= n; m <<= 1);
		memset(cf, 0, m * sizeof(int));
		for(int i = 1; i <= n; ++i) {
			memset(vis, 0, m * sizeof(bool));
			for(int j = 1, k = 1; j <= i; j += (k++) << 1 | 1) {
				mx = max(mx, sf[i - j] ^ sf[i - 1]);
				vis[sf[i - j] ^ sf[i - 1]] = 1;
			}
			for(f[i] = 0; vis[f[i]]; ++f[i]);
			mx = max(mx, f[i]);
			assert(f[i] < m);
			sf[i] = sf[i - 1] ^ f[i];
			for(int j = 1, k = 1; j <= i; j += (k++) << 1 | 1) {
				mx = max(mx, sf[i - j] ^ sf[i]);
				++cf[sf[i - j] ^ sf[i]];
			}
		}
		memset(cg, 0, m * sizeof(int));
		for(int i = 1; i <= n; ++i) {
			memset(vis, 0, m * sizeof(bool));
			for(int j = 1, k = 1; j <= i; j += ++k) {
				mx = max(mx, sg[i - j] ^ sg[i - 1]);
				vis[sg[i - j] ^ sg[i - 1]] = 1;
			}
			for(g[i] = 0; vis[g[i]]; ++g[i]);
			mx = max(mx, g[i]);
			assert(g[i] < m);
			sg[i] = sg[i - 1] ^ g[i];
			for(int j = 1, k = 1; j <= i; j += ++k) {
				mx = max(mx, sg[i - j] ^ sg[i]);
				++cg[sg[i - j] ^ sg[i]];
			}
		}
		int val = calc(sf[n], sg[n]);
		LL ans = 0;
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < m; ++j)
				if(calc(i, j) == val)
					ans += (LL)cf[i] * cg[j];
		printf("%lld\n", ans);
		printf("%d\n", mx);
	}
	return 0;
}
