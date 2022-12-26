#include <bits/stdc++.h>
using namespace std;
const int maxm = (int)1e4 + 1, maxc = (int)1e3 + 1, maxs = (int)1e7 + 1, INF = 0x3f3f3f3f;
int n, m, c0, c1, a[maxm], dis[maxm], que0[maxm], que1[(maxc * maxc) << 1 | 1];
bool vis[maxs];
inline int idx(int u, int x) {
	return u * c0 + x;
}
inline void rdx(int id, int &u, int &x) {
	u = id / c0;
	x = id % c0;
}
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++i)
			scanf("%d", a + i);
		scanf("%d%d", &c0, &c1);
		sort(a, a + m);
		m = unique(a, a + m) - a;
		int ans = INF;
		memset(dis, 0x3f, m * sizeof(int));
		// memset(vis, 0, m * c0 * sizeof(bool));
		dis[0] = que0[0] = 0;
		for(int i = 0, tot0 = 1; i < tot0; ++i) {
			int u = que0[i], tmp;
			if(a[m - 1] - a[u] <= c0)
				ans = min(ans, dis[u] * (c0 + c1) + a[m - 1] - a[u]);
			if(ans < INF)
				continue;
			vis[tmp = idx(u, 0)] = 1;
			que1[0] = tmp;
			for(int j = 0, tot1 = 1; j < tot1; ++j) {
				tmp = que1[j];
				int v, x, w, y;
				rdx(tmp, v, x);
				if(v > 0 && (y = x + a[v] - a[v - 1]) <= c0) {
					w = v - 1;
					if(y == c0) {
						if(dis[w] == INF) {
							dis[w] = dis[u] + 1;
							que0[tot0++] = w;
						}
					} else if(!vis[tmp = idx(w, y)]) {
						vis[tmp] = 1;
						que1[tot1++] = tmp;
					}
				}
				if(v < m - 1 && (y = x + a[v + 1] - a[v]) <= c0) {
					w = v + 1;
					if(y == c0) {
						if(dis[w] == INF) {
							dis[w] = dis[u] + 1;
							que0[tot0++] = w;
						}
					} else if(!vis[tmp = idx(w, y)]) {
						vis[tmp] = 1;
						que1[tot1++] = tmp;
					}
				}
			}
		}
		printf("%d\n", ans < INF ? ans : -1);
	}
	return 0;
}