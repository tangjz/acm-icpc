#include <cstdio>
#include <cstring>
const int maxn = 501, maxm = 1501, maxv = 5, maxt = 201;
int t, n, m, vol, lim, pr[maxn], lnk[maxn], f[maxt][maxv][maxn];
struct Edge {
	int nxt, v, w, c;
} e[maxm];
inline void upd(int &x, int y) {
	x < y && (x = y);
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int nn, mm, kk, ans = -1;
		memset(f, -1, sizeof f);
		scanf("%d%d%d%d%d%d", &nn, &mm, &vol, &kk, &f[0][0][0], &lim);
		n = nn * kk;
		for(int i = 0; i < n; ++i)
			scanf("%d", pr + i);
		m = 0;
		memset(lnk, -1, n * sizeof(int));
		while(mm--) {
			int u, v, w, c;
			scanf("%d%d%d%d", &u, &v, &w, &c);
			if(u == nn)
				continue;
			for(int i = 0, iLim = u > 1 && u < nn && v > 1 && v < nn ? kk : 1; i < iLim; ++i) {
				int uu = i * nn + u - 1, vv = i * nn + v - 1;
				e[m] = (Edge){lnk[uu], vv, w, c};
				lnk[uu] = m++;
			}
		}
		for(int i = 2; i < nn; ++i)
			for(int u = i - 1, v = u + nn < n ? u + nn : u + nn - n; u < n; u += nn, ((v += nn) >= n && (v -= n))) {
				e[m] = (Edge){lnk[u], v, 1, 0};
				lnk[u] = m++;
			}
		for(int i = 0; i <= lim; ++i)
			for(int j = 0; j <= vol; ++j) {
				for(int k = 0; k < n; ++k) {
					if(f[i][j][k] == -1)
						continue;
					for(int it = lnk[k]; it != -1; it = e[it].nxt) {
						int x = i + e[it].w, y = e[it].v, z = f[i][j][k] - e[it].c;
						if(x > lim || z < 0)
							continue;
						upd(f[x][j][y], z);
						if(pr[y] != -1) {
							if(j > 0)
								upd(f[x][j - 1][y], z + pr[y]);
							if(j < vol)
								upd(f[x][j + 1][y], z - pr[y]);
						}
					}
				}
				upd(ans, f[i][j][nn - 1]);
			}
		if(ans == -1)
			printf("Case #%d: Forever Alone\n", Case);
		else
			printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
