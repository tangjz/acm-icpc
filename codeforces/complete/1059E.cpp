#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, m, w[maxn], fa[maxn], dep[maxn], tot, path[maxn], sum[maxn], ans;
LL lim, s[maxn];
vector<int> e[maxn], rem[maxn];
set<int> sp[2][maxn];
void pfs(int u, int id) {
	path[tot++] = u;
	for( ; dep[u] - dep[path[id]] > m || s[u] - s[path[id]] > lim; ++id);
	++sum[u];
	--sum[path[id]];
	rem[path[id]].push_back(u);
	for(int v : e[u])
		pfs(v, id);
	--tot;
}
void merge(set<int> &lft, set<int> &rht) {
	if(lft.size() < rht.size())
		lft.swap(rht);
	for(int v : rht)
		lft.insert(v);
	set<int>().swap(rht);
}
void dfs(int u) {
	sp[1][u].insert(u);
	for(int v : e[u]) {
		dfs(v);
		sum[u] += sum[v];
		merge(sp[0][u], sp[0][v]);
		merge(sp[1][u], sp[1][v]);
	}
	for(int v : rem[u]) {
		if(sp[0][u].count(v))
			sp[0][u].erase(v);
		if(sp[1][u].count(v))
			sp[1][u].erase(v);
	}
	if(sp[0][u].empty() && !sp[1][u].empty()) {
		++ans;
		merge(sp[0][u], sp[1][u]);
	}
}
int main() {
	scanf("%d%d%lld", &n, &m, &lim);
	for(int i = 1; i <= n; ++i)
		scanf("%d", w + i);
	dep[1] = 1;
	s[1] = w[1];
	for(int i = 2; i <= n; ++i) {
		scanf("%d", fa + i);
		e[fa[i]].push_back(i);
		dep[i] = dep[fa[i]] + 1;
		s[i] = s[fa[i]] + w[i];
	}
	path[tot++] = 0;
	pfs(1, 0);
	dfs(1);
	for(int i = 1; i <= n; ++i)
		if(sum[i] <= 0) {
			puts("-1");
			return 0;
		}
	printf("%d\n", ans);
	return 0;
}
