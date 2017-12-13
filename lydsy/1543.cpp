#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 50001, maxm = 100001, maxs = 7, mod = 1000003;
int n, m, blk, dsu[maxn], val, cnt, sum, ans;
struct Edge {
	int u, v, w;
	void read() {
		scanf("%d%d%d", &u, &v, &w);
	}
	bool operator < (Edge const &t) const {
		return w < t.w;
	}
} e[maxm << 1 | 1];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : dsu_find(dsu[x]);
}
bool dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return 0;
	if(dsu[u] < dsu[v])
		std::swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[v];
	dsu[u] = v;
	return 1;
}
void dfs(int dep, int ctr) {
	if(dep == m || e[dep].w != val) {
		if(cnt < ctr) {
			cnt = ctr;
			sum = 0;
		}
		sum += cnt == ctr;
		return;
	}
	dfs(dep + 1, ctr);
	int u = dsu_find(e[dep].u), v = dsu_find(e[dep].v), du = dsu[u], dv = dsu[v];
	if(dsu_merge(u, v)) {
		dfs(dep + 1, ctr + 1);
		dsu[u] = du;
		dsu[v] = dv;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		e[i].read();
	std::sort(e, e + m);
	ans = 1;
	blk = n;
	memset(dsu, -1, n * sizeof(int));
	for(int i = 0; i < m; ) {
		cnt = sum = 0;
		val = e[i].w;
		dfs(i, 0);
		ans = ans * sum % mod;
		for( ; i < m && e[i].w == val; ++i)
			blk -= dsu_merge(e[i].u, e[i].v);
	}
	printf("%d\n", blk == 1 ? ans : 0);
	return 0;
}

