#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1, maxm = (int)1e6 + 1, maxd = 11, INF = 0x3f3f3f3f;
int t, n, m, a[maxn][maxn], dsu[maxn], dis[maxn];
LL ans;
struct Edge {
	int u, v, w;
	bool operator < (Edge const &t) const {
		return w > t.w;
	}
} e[maxm];
int dsu_find(int x) {
	for( ; dsu[x] >= 0; x = dsu[x]);
	return x;
}
bool dsu_merge(int u, int v, int w) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return 0;
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	dis[u] = w;
	return 1;
}
int dsu_query(int u, int v) {
	int ret = INF;
	static int sz[2], que[2][maxd];
	for(sz[0] = 0; dsu[u] >= 0; u = dsu[u])
		que[0][sz[0]++] = u;
	for(sz[1] = 0; dsu[v] >= 0; v = dsu[v])
		que[1][sz[1]++] = v;
	for( ; sz[0] && sz[1] && que[0][sz[0] - 1] == que[1][sz[1] - 1]; --sz[0], --sz[1]);
	for( ; sz[0]; ret = min(ret, dis[que[0][--sz[0]]]));
	for( ; sz[1]; ret = min(ret, dis[que[1][--sz[1]]]));
	return ret;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		m = ans = 0;
		for(int i = 0; i < n; ++i) {
			dsu[i] = -1;
			dis[i] = INF;
			for(int j = 0; j < n; ++j) {
				scanf("%d", a[i] + j);
				if(i <= j)
					continue;
				ans += abs(a[i][j] - a[j][i]);
				e[m++] = (Edge){i, j, max(a[i][j], a[j][i])};
			}
		}
		sort(e, e + m);
		for(int i = 0; i < m; ++i) {
			int u = e[i].u, v = e[i].v, w = e[i].w;
			if(!dsu_merge(u, v, w))
				ans += (dsu_query(u, v) - w) << 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
