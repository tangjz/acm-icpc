#include <bits/stdc++.h>
using namespace std;
const int maxn = 501, maxm = maxn * maxn;
const int d[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int n, p[maxm], dis[maxm];
bool vis[maxm];
inline int idx(int x, int y) {
	return x * n + y;
}
inline void rdx(int id, int &x, int &y) {
	x = id / n;
	y = id % n;
}
int main() {
	scanf("%d", &n);
	int m = n * n;
	for(int i = 0; i < m; ++i) {
		scanf("%d", p + i);
		--p[i];
	}
	for(int i = 0, id = 0; i < n; ++i)
		for(int j = 0; j < n; ++j, ++id) {
			dis[id] = min(min(i + 1, n - i), min(j + 1, n - j));
			vis[id] = 0;
		}
	int ans = 0;
	for(int i = 0; i < m; ++i) {
		vis[p[i]] = 1;
		ans += --dis[p[i]];
		queue<int> Q;
		Q.push(p[i]);
//		printf("force dis (%d, %d) <- %d\n", p[i] / n, p[i] % n, dis[p[i]]);
		while(!Q.empty()) {
			int u = Q.front(), ux, uy;
			Q.pop();
			rdx(u, ux, uy);
			for(int k = 0; k < 4; ++k) {
				int vx = ux + d[k][0], vy = uy + d[k][1];
				if(vx < 0 || vx >= n || vy < 0 || vy >= n)
					continue;
				int v = idx(vx, vy), tmp = dis[u] + !vis[v];
				if(dis[v] > tmp) {
//					printf("dis (%d, %d) <- %d\n", vx, vy, tmp);
					dis[v] = tmp;
					Q.push(v);
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}