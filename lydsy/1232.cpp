#include <cstdio>
#include <algorithm>
const int maxn = 10001, maxm = 100001;
int n, m, a[maxn], dsu[maxn], ans;
struct Edge {
	int u, v, w;
	bool operator < (Edge const &t) const {
		return w < t.w;
	}
} e[maxm];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
bool dsu_merge(int u, int v) {
	if((u = dsu_find(u)) == (v = dsu_find(v)))
		return 0;
	if(dsu[u] > dsu[v])
		std::swap(dsu[u], dsu[v]);
	if(dsu[u] == dsu[v])
		--dsu[u];
	dsu[v] = u;
	return 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		dsu[i] = -1;
		if(a[ans] > a[i])
			ans = i;
	}
	ans = a[ans];
	for(int i = 0; i < m; ++i) {
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		e[i].w = (e[i].w << 1) + a[--e[i].u] + a[--e[i].v];
	}
	std::sort(e, e + m);
	for(int i = 0; i < m; ++i)
		if(dsu_merge(e[i].u, e[i].v))
			ans += e[i].w;
	printf("%d\n", ans);
	return 0;
}
