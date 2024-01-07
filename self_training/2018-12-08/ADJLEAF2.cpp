#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e5 + 1, maxd = 19;
int n, m, ord[maxn], dep[maxn], fa[maxd][maxn], qtot, que[maxn], stot, stk[maxn], gfa[maxn], f[maxn];
vector<int> e[maxn], g[maxn];
bool ban[maxd][maxn];
void pfs(int u) {
	ord[u] = ++qtot;
	for(int v : e[u]) {
		if(v == fa[0][u])
			continue;
		dep[v] = dep[u] + 1;
		ban[0][v] = e[v].size() >= 3;
		fa[0][v] = u;
		for(int i = 1; i < maxd && fa[i - 1][v]; ++i) {
			ban[i][v] = ban[i - 1][v] || ban[i - 1][fa[i - 1][v]];
			fa[i][v] = fa[i - 1][fa[i - 1][v]];
		}
		pfs(v);
	}
}
int lca(int u, int v) {
	if(dep[u] < dep[v])
		swap(u, v);
	for(int i = dep[u] - dep[v], j = 0; i > 0; i >>= 1, ++j)
		(i & 1) && (u = fa[j][u]);
	if(u == v)
		return u;
	for(int i = maxd - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
bool check(int u, int v) {
	int p = lca(u, v);
	if(u != p && v != p && ban[0][p])
		return 1;
	u = fa[0][u];
	for(int i = dep[u] - dep[p], j = 0; i > 0; i >>= 1, ++j)
		if(i & 1) {
			if(ban[j][u])
				return 1;
			u = fa[j][u];
		}
	v = fa[0][v];
	for(int i = dep[v] - dep[p], j = 0; i > 0; i >>= 1, ++j)
		if(i & 1) {
			if(ban[j][v])
				return 1;
			v = fa[j][v];
		}
	return 0;
}
void dfs(int u, int p) {
	int ctr1 = 0, ctr2 = 0, ctr4 = 0;
	for(int v : g[u]) {
		if(v == p)
			continue;
		dfs(v, u);
		if(!(f[v] & 1) || check(u, v)) {
			++ctr1;
			if(f[v] & 2)
				++ctr2;
			else
				ctr2 = maxn;
		}
		if(f[v] & 4)
			++ctr4;
	}
	f[u] = (!ctr1 && e[u].size() == g[u].size()) | (ctr2 <= 1) << 1 | (ctr2 <= 2 || (ctr4 == 1 && g[u].size() - (p != -1) == 1)) << 2;
	vector<int>().swap(g[u]);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dep[0] = -1;
	ban[0][1] = e[1].size() >= 3;
	pfs(1);
	while(m--) {
		int rt;
		scanf("%d%d", &rt, &qtot);
		for(int i = 0; i < qtot; ++i)
			scanf("%d", que + i);
		que[qtot++] = rt;
		sort(que, que + qtot, [&ord](int const &u, int const &v) {
			return ord[u] < ord[v];
		});
		stot = 0;
		g[0].push_back(que[0]);
		gfa[que[0]] = 0;
		stk[++stot] = que[0];
		for(int i = 1, iLim = qtot; i < iLim; ++i) {
			int p = stot ? lca(stk[stot], que[i]) : 0;
			for( ; dep[stk[stot]] > dep[p]; --stot);
			if(dep[stk[stot]] < dep[p]) {
				int v = g[stk[stot]].back();
				gfa[p] = stk[stot];
				g[stk[stot]].back() = p;
				gfa[v] = p;
				g[p].push_back(v);
				stk[++stot] = p;
				que[qtot++] = p;
			}
			g[p].push_back(que[i]);
			gfa[que[i]] = p;
			stk[++stot] = que[i];
		}
		vector<int>().swap(g[0]);
		for(int i = 0; i < qtot; ++i)
			if(gfa[que[i]])
				g[que[i]].push_back(gfa[que[i]]);
		dfs(rt, -1);
		puts(f[rt] & 4 ? "YES" : "NO");
	}
	return 0;
}
