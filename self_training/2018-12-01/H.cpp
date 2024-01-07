#include <bits/stdc++.h>
using namespace std;
const int maxn = 101, INF = 1 << 25;
int t, n, m, q, e[maxn][maxn], p[maxn], cur, pre = 1;
__int128 f[2][maxn];
pair<__int128, int> g[maxn];
inline void upd(pair<__int128, int> &cur, __int128 val, int cnt) {
	if(cur.first > val || (cur.first == val && cur.second < cnt))
		cur = make_pair(val, cnt);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &m, &q);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				e[i][j] = i == j ? 0 : INF;
		while(m--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if(e[u][v] > w)
				e[u][v] = e[v][u] = w;
		}
		for(int i = 1; i <= q; ++i)
			scanf("%d", p + i);
		for(int k = 1; k <= n; ++k)
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
					e[i][j] = min(e[i][j], e[i][k] + e[k][j]);
		for(int i = 0; i <= q; ++i)
			g[i] = make_pair((__int128)INF << i, 0);
		upd(g[0], e[1][n], 0);
		for(int i = 1; i <= q; ++i) {
			f[cur][i] = e[1][p[i]];
			upd(g[1], (f[cur][i] << 1) + e[p[i]][n], 1);
			for(int j = 1; j <= q; ++j)
				if(i != j)
					upd(g[0], f[cur][i] + e[p[i]][p[j]], INF);
		}
		for(int i = 2; i <= q; ++i) {
			swap(cur, pre);
			for(int j = 1; j <= q; ++j) {
				f[cur][j] = (__int128)INF << i;
				for(int k = 1; k <= q; ++k)
					if(j != k)
						f[cur][j] = min(f[cur][j], (f[pre][k] << 1) + e[p[k]][p[j]]);
				upd(g[i], (f[cur][j] << 1) + e[p[j]][n], i);
				for(int k = 1; k <= q; ++k)
					if(j != k)
						upd(g[i - 1], f[cur][j] + e[p[j]][p[k]], INF);
			}
		}
		int pos = 0;
		for(int i = 1; i <= q; ++i) {
			__int128 tmp = g[pos].first << (i - pos);
			if(g[i].first < tmp || (g[i].first == tmp && g[i].second > g[pos].second))
				pos = i;
		}
		double ans = g[pos].first;
		for(int i = 0; i < pos; ++i)
			ans /= 2;
		if(g[pos].second < INF) {
			printf("%.20f %d\n", (double)ans, g[pos].second);
		} else {
			printf("%.20f Burst!\n", (double)ans);
		}
	}
	return 0;
}
