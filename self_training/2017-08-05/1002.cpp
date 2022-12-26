#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 3001, maxm = 100001, maxd = 13, INF = 0x3f3f3f3f, maxt = 10;
int n, m, e[maxn][maxn], dsu[maxn], dt[maxn], dep[maxn], fa[maxd][maxn], ans;
struct Edge {
	int u, v, w;
	bool used;
	bool operator < (Edge const &t) const {
		return w > t.w;
	}
} g[maxm];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
bool dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return 0;
	if(dsu[u] < dsu[v])
		swap(u, v);
	else if(dsu[u] == dsu[v])
		--dsu[v];
	dsu[u] = v;
	return 1;
}
vector<pair<int, int> > ee[maxn];
void pfs(int u) {
	for(vector<pair<int, int> >::iterator it = ee[u].begin(); it != ee[u].end(); ++it) {
		int v = it -> first;
		if(v == fa[0][u])
			continue;
		dt[v] = 0;
		dep[v] = dep[u] + 1;
		fa[0][v] = u;
		pfs(v);
	}
}
int lca(int u, int v) {
	for(int i = 0, j = dep[u] - dep[v]; j > 0; ++i, j >>= 1)
		(j & 1) && (u = fa[i][u]);
	for(int i = 0, j = dep[v] - dep[u]; j > 0; ++i, j >>= 1)
		(j & 1) && (v = fa[i][v]);
	if(u == v)
		return u;
	for(int i = maxd - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
void dfs(int u) {
	for(vector<pair<int, int> >::iterator it = ee[u].begin(); it != ee[u].end(); ++it) {
		int v = it -> first, w = it -> second;
		if(v == fa[0][u])
			continue;
		dfs(v);
		ans = min(ans, w + dt[v]);
		dt[u] += dt[v];
	}
}
#include <ctime>
int perm[maxm];
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 1; i <= n; ++i)
			memset(e[i] + 1, 0, n * sizeof(int));
		while(m--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if(u > v)
				swap(u, v);
			e[u][v] += w;
		}
		m = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = i + 1; j <= n; ++j)
				if(e[i][j])
					g[m++] = (Edge){i, j, e[i][j], 0};
		sort(g, g + m);
		ans = INF;
		for(int i = 0; i < m; ++i)
			perm[i] = i;
		for(int Case = 1; Case < maxt; ++Case) {
			int blk = n;
			memset(dsu + 1, -1, n * sizeof(int));
			for(int i = 1; i <= n; ++i)
				vector<pair<int, int> >().swap(ee[i]);
			for(int i = 0; i < m; ++i)
				if((g[i].used = dsu_merge(g[i].u, g[i].v))) {
					ee[g[i].u].push_back(make_pair(g[i].v, g[i].w));
					ee[g[i].v].push_back(make_pair(g[i].u, g[i].w));
					--blk;
					// printf("tree %d %d %d\n", g[i].u, g[i].v, g[i].w);
				}
			if(blk > 1) {
				ans = 0;
				break;
			}
			pfs(1);
			for(int i = 1; i < maxd; ++i)
				for(int j = 1; j <= n; ++j)
					fa[i][j] = fa[i - 1][fa[i - 1][j]];
			for(int i = 0; i < m; ++i)
				if(!g[i].used) {
					// printf("non-tree %d %d %d\n", g[i].u, g[i].v, g[i].w);
					int pp = lca(g[i].u, g[i].v);
					dt[g[i].u] += g[i].w;
					dt[g[i].v] += g[i].w;
					dt[pp] -= g[i].w << 1;
				}
			dfs(1);
			for(int i = 0; i < m; ++i) {
				swap(perm[i], perm[i + (rand() << 15 | rand()) % (m - i)]);
				swap(g[i], g[perm[i]]);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

