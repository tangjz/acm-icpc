#include <bits/stdc++.h>
using namespace std;
const int maxn = 200001, maxd = 18, INF = 0x3f3f3f3f;
int t, n, m, dsu[maxn], low[maxn], mx, fa[maxd][maxn];
pair<int, int> ans[maxn];
set<pair<int, int> > sp[maxn];
struct Edge {
	int u, v, w;
	void read() {
		scanf("%d%d%d", &u, &v, &w);
	}
	bool operator < (Edge const &t) const {
		return w < t.w;
	}
} e[maxn];
int getRoot(int u) {
	return !dsu[u] ? u : dsu[u] = getRoot(dsu[u]);
}
void mergeRoot(int u, int v, int w) {
	dsu[++n] = 0;
	fa[0][n] = 0;
	dsu[u] = dsu[v] = fa[0][u] = fa[0][v] = n;
	low[n] = w;
	ans[n] = max(ans[u], ans[v]);
	set<pair<int, int> >().swap(sp[n]);
	if(sp[u].size() < sp[v].size())
		swap(u, v);
	sp[n].swap(sp[u]);
	for(set<pair<int, int> >::iterator it = sp[v].begin(), jt; it != sp[v].end(); jt = it++, sp[v].erase(jt)) {
		int typ = it -> first, ctr = it -> second;
		jt = sp[n].lower_bound(make_pair(typ, 0));
		if(jt != sp[n].end() && (jt -> first) == typ) {
			ctr += jt -> second;
			sp[n].erase(jt);
			ans[n] = max(ans[n], make_pair(ctr, -typ));
		}
		sp[n].insert(make_pair(typ, ctr));
	}
}
int main() {
	low[0] = INF;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			int typ;
			scanf("%d", &typ);
			dsu[i] = fa[0][i] = low[i] = 0;
			ans[i] = make_pair(1, -typ);
			sp[i].insert(make_pair(typ, 1));
		}
		for(int i = 1; i <= m; ++i)
			e[i].read();
		sort(e + 1, e + m + 1);
		for(int i = 1; i <= m; ++i) {
			int u = getRoot(e[i].u);
			int v = getRoot(e[i].v);
			if(u != v)
				mergeRoot(u, v, e[i].w);
		}
		for(int i = 1; i <= n; ++i)
			set<pair<int, int> >().swap(sp[i]);
		for(mx = 1; (1 << mx) <= n; ++mx)
			for(int i = 1; i <= n; ++i)
				fa[mx][i] = fa[mx - 1][fa[mx - 1][i]];
		scanf("%d", &m);
		printf("Case #%d:\n", Case);
		int last = 0;
		while(m--) {
			int x, w;
			scanf("%d%d", &x, &w);
			x ^= last;
			w ^= last;
			for(int i = mx - 1; i >= 0; --i)
				if(low[fa[i][x]] <= w)
					x = fa[i][x];
			printf("%d\n", last = -ans[x].second);
		}
	}
	return 0;
}
