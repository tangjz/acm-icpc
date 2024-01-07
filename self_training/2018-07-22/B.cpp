#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e3 + 1;
int t, n, m, lch[maxn], rch[maxn], seq[2][maxn], dsu[maxn];
void pfs(int u) {
	if(!u)
		return;
	seq[0][++seq[0][0]] = u;
	pfs(lch[u]);
	pfs(rch[u]);
}
void dfs(int u) {
	if(!u)
		return;
	dfs(lch[u]);
	dfs(rch[u]);
	seq[1][++seq[1][0]] = u;
}
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
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	return 1;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			scanf("%d%d", lch + i, rch + i);
			dsu[i] = -1;
		}
		seq[0][0] = seq[1][0] = 0;
		pfs(1);
		dfs(1);
		int cnt = n;
		for(int i = 1; i <= n; ++i)
			cnt -= dsu_merge(seq[0][i], seq[1][i]);
		if(cnt < m) {
			printf("Case #%d: Impossible\n", Case);
		} else {
			for(int i = 1; i <= n; ++i)
				if(i == dsu_find(i))
					dsu[i] = -((--cnt) % m + 1);
			printf("Case #%d:", Case);
			for(int i = 1; i <= n; ++i)
				printf(" %d", -dsu[dsu_find(i)]);
			printf("\n");
		}
	}
	return 0;
}
