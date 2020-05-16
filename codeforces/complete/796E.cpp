#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1, maxd = 51;
int n, m, d, f[2][maxd][maxd][maxn], cur, pre = 1;
bool lft[maxn], rht[maxn];
int main() {
	scanf("%d%d%d", &n, &m, &d);
	m = min(m, ((n - 1) / d + 1) << 1);
	auto init = [](bool vis[]) {
		int c, x;
		scanf("%d", &c);
		while(c--) {
			scanf("%d", &x);
			vis[x] = 1;
		}
	};
	init(lft);
	init(rht);
	auto upd = [](int &u, int v) {
		u < v && (u = v);
	};
	auto clear = [&m, &d](int (*f)[maxd][maxn]) {
		for(int i = 0; i <= d; ++i)
			for(int j = 0; j <= d; ++j)
				memset(f[i][j], -1, (m + 1) * sizeof(int));
	};
	clear(f[cur]);
	f[cur][0][0][0] = 0;
	for(int i = 1; i <= n; ++i) {
		swap(cur, pre);
		clear(f[cur]);
		for(int x = 0; x <= d; ++x) {
			int xx = x ? x - 1 : 0;
			for(int y = 0; y <= d; ++y) {
				int yy = y ? y - 1 : 0;
				for(int j = 0; j <= m; ++j) {
					if(f[pre][x][y][j] == -1)
						continue;
					upd(f[cur][xx][yy][j], f[pre][x][y][j] + ((xx && lft[i]) || (yy && rht[i])));
					if(j < m) {
						upd(f[cur][d][yy][j + 1], f[pre][x][y][j] + (lft[i] || (yy && rht[i])));
						upd(f[cur][xx][d][j + 1], f[pre][x][y][j] + ((xx && lft[i]) || rht[i]));
						if(j + 1 < m)
							upd(f[cur][d][d][j + 2], f[pre][x][y][j] + (lft[i] || rht[i]));
					}
				}
			}
		}
	}
	int ans = 0;
	for(int x = 0; x <= d; ++x)
		for(int y = 0; y <= d; ++y)
			for(int i = 0; i <= m; ++i)
				upd(ans, f[cur][x][y][i]);
	printf("%d\n", ans);
	return 0;
}