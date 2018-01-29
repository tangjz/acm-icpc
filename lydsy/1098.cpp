#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, dsu[maxn], ans, out[maxn];
vector<int> e[maxn];
int dsu_find(int x) {
	return x == dsu[x] ? x : dsu[x] = dsu_find(dsu[x]);
}
void dfs(int u) {
	++out[ans];
	dsu[u] = dsu_find(u - 1);
	vector<int>::iterator it = e[u].begin();
	for(int v = dsu_find(n); v; v = dsu_find(v - 1)) {
		for( ; it != e[u].end() && *it > v; ++it);
		if(it == e[u].end() || *it != v)
			dfs(v);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i = 1; i <= n; ++i) {
		dsu[i] = i;
		sort(e[i].begin(), e[i].end(), greater<int>());
		unique(e[i].begin(), e[i].end());
	}
	for(int u = dsu_find(n); u; u = dsu_find(n), ++ans)
		dfs(u);
	printf("%d\n", ans);
	sort(out, out + ans);
	for(int i = 0; i < ans; ++i)
		printf("%d ", out[i]);
	puts("");
	return 0;
}
