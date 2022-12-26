#include <bits/stdc++.h>
using namespace std;
const int maxn = 21, maxm = 401, maxd = 1 << 7 | 1, maxs = 400 << 7 | 1, maxt = 400, INF = ~0u >> 1;
int t, n, m, q, mat[maxn][maxn], tot, val[maxm], col[maxm], f[maxs], que[maxs];
int main() {
	srand(time(0));
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &m, &q);
		tot = 0;
		memset(col, -1, sizeof col);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j) {
				scanf("%d", mat[i] + j);
				if(mat[i][j] > 0 && col[mat[i][j]] == -1) {
					col[mat[i][j]] = 0;
					val[tot++] = mat[i][j];
				}
			}
		int ans = INF;
		col[0] = 0;
		for(int o = 0; o < maxt; ++o) {
			for(int i = 0; i < tot; ++i)
				col[val[i]] = 1 << (rand() % q);
			memset(f, -1, ((n * m) << q) * sizeof(int));
			int tot = 0;
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < m; ++j)
					if(mat[i][j] != -1) {
						int s = ((i * m + j) << q) | col[mat[i][j]];
						f[s] = 0;
						que[tot++] = s;
					}
			for(int i = 0; i < tot; ++i) {
				int udx = que[i], ux = (udx >> q) / m, uy = (udx >> q) % m, us = udx & ((1 << q) - 1);
				if(us == (1 << q) - 1)
					ans = min(ans, f[udx]);
				for(int dx = -1; dx <= 1; ++dx)
					for(int dy = -1; dy <= 1; ++dy) {
						if((dx != 0) == (dy != 0))
							continue;
						int vx = ux + dx, vy = uy + dy;
						if(vx < 0 || vx >= n || vy < 0 || vy >= m || mat[vx][vy] == -1)
							continue;
						int vs = us | col[mat[vx][vy]], vdx = ((vx * m + vy) << q) | vs;
						if(f[vdx] == -1) {
							f[vdx] = f[udx] + 1;
							que[tot++] = vdx;
						}
					}
			}
		}
		printf("%d\n", ans < INF ? ans : -1);
	}
	return 0;
}
