#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e3 + 1, maxm = (int)2e5 + 1;
int n, m, tot, pre[maxn], suf[maxn], fa[maxn], ord[maxn], rnk[maxn];
int lnk[maxn], dsu[maxn], pos[maxn], idom[maxn], sdom[maxn];
struct Edge {
	int nxt, v;
} e[maxm * 3];
bool cmp(int u, int v) {
	return rnk[u] < rnk[v];
}
int dsu_find(int u) {
	if(dsu[u] == u)
		return u;
	int tp = dsu[u];
	dsu[u] = dsu_find(tp);
	if(cmp(sdom[pos[tp]], sdom[pos[u]]))
		pos[u] = pos[tp];
	return dsu[u];
}
void dfs(int u) {
	ord[tot] = u;
	rnk[u] = tot++;
	for(int it = pre[u]; it != -1; it = e[it].nxt)
		if(rnk[e[it].v] == -1) {
			fa[e[it].v] = u;
			dfs(e[it].v);
		}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		pre[i] = suf[i] = lnk[i] = rnk[i] = -1;
		dsu[i] = pos[i] = sdom[i] = i;
	}
	for(int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i << 1] = (Edge){pre[--u], --v};
		pre[u] = i << 1;
		e[i << 1 | 1] = (Edge){suf[v], u};
		suf[v] = i << 1 | 1;
	}
	m <<= 1;
	fa[0] = -1;
	dfs(0);
	for(int i = n - 1; i >= 1; --i) {
		int u = ord[i];
		for(int it = suf[u]; it != -1; it = e[it].nxt) {
			dsu_find(e[it].v);
			if(cmp(sdom[pos[e[it].v]], sdom[u]))
				sdom[u] = sdom[pos[e[it].v]];
		}
		e[m] = (Edge){lnk[sdom[u]], u};
		lnk[sdom[u]] = m++;
		dsu[u] = fa[u];
		for(int it = lnk[fa[u]]; it != -1; it = e[it].nxt) {
			dsu_find(e[it].v);
			idom[e[it].v] = sdom[pos[e[it].v]] == sdom[e[it].v] ? fa[u] : pos[e[it].v];
		}
		lnk[fa[u]] = -1;
	}
	for(int i = 1; i < n; ++i) {
		int u = ord[i];
		idom[u] = idom[u] == sdom[u] ? idom[u] : idom[idom[u]];
	}
	m = tot = 0;
	for(int i = 0; i < n; ++i) {
		int u = ord[i];
		lnk[u] = -1;
		if(cmp(idom[u], u)) {
			tot += lnk[idom[u]] == -1;
			e[m] = (Edge){lnk[idom[u]], u};
			lnk[idom[u]] = m++;
		}
	}
	printf("%d\n", tot);
	for(int i = 0, j = 0; i < n; ++i) {
		if(lnk[i] == -1)
			continue;
		if(j)
			putchar(' ');
		else
			j = 1;
		printf("%d", i + 1);
	}
	putchar('\n');
	return 0;
}
