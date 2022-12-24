#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e4 + 1;
int n, m, q, dsu[maxn], ord[maxn], ans;
struct Edge {
	int u, v, w1, w2;
	void read() {
		scanf("%d%d%d%d", &u, &v, &w1, &w2);
	}
} e[maxn];
bool cmp1(int const &u, int const &v) {
	return e[u].w1 < e[v].w1;
}
bool cmp2(int const &u, int const &v) {
	return e[u].w2 < e[v].w2;
}
int dsu_find(int u) {
	return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
}
bool dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return 0;
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	return 1;
}
int main() {
	scanf("%d%d%d", &n, &q, &m);
	--m;
	for(int i = 0; i < m; ++i) {
		e[i].read();
		ord[i] = i;
	}
	memset(dsu + 1, -1, n * sizeof(int));
	sort(ord, ord + m, cmp1);
	for(int i = 0, j = 0; i < m && j < q; ++i)
		if(dsu_merge(e[ord[i]].u, e[ord[i]].v)) {
			ans = max(ans, e[ord[i]].w1);
			swap(ord[i], ord[j++]);
		}
	sort(ord + q, ord + m, cmp2);
	for(int i = q; i < m; ++i)
		if(dsu_merge(e[ord[i]].u, e[ord[i]].v))
			ans = max(ans, e[ord[i]].w2);
	printf("%d\n", ans);
	return 0;
}
