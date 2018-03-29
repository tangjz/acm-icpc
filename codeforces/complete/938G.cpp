#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> Pair;
typedef pair<Pair, int> Triple;
const int maxn = (int)2e5 + 1, maxd = 19, maxb = 31;
int n, qtot, htot, dsu[maxn], msk[maxn];
Pair que[maxn], his[maxn << 1 | 1];
Pair dsu_find(int u) {
	int ret = 0;
	for( ; dsu[u] >= 0; ret ^= msk[u], u = dsu[u]);
	return (Pair){u, ret};
}
int dsu_merge(int u, int v, int w) {
	Pair pu = dsu_find(u), pv = dsu_find(v);
	w ^= pu.second ^ pv.second;
	if((u = pu.first) == (v = pv.first))
		return w;
	if(dsu[u] < dsu[v])
		swap(u, v);
	his[htot++] = (Pair){u, dsu[u]};
	his[htot++] = (Pair){v, dsu[v]};
	if(dsu[u] == dsu[v])
		--dsu[v];
	dsu[u] = v;
	msk[u] = w;
	return 0;
}
int base[maxd][maxb];
vector<Triple> e[maxn << 1 | 1];
void update(int L, int R, int l, int r, Triple v) {
	if(l <= L && R <= r) {
		e[(L + R) | (L < R)].push_back(v);
	} else {
		int M = (L + R) >> 1;
		if(l <= M)
			update(L, M, l, r, v);
		if(M < r)
			update(M + 1, R, l, r, v);
	}
}
void solve(int dep, int L, int R) {
	int rt = (L + R) | (L < R), pht = htot;
	for(vector<Triple>::iterator it = e[rt].begin(); it != e[rt].end(); ++it) {
		int tmp = dsu_merge(it -> first.first, it -> first.second, it -> second);
		for(int i = 1; i <= base[dep][0] && tmp; ++i)
			tmp = min(tmp, tmp ^ base[dep][i]);
		if(tmp) {
			for(int i = 1; i <= base[dep][0]; ++i)
				base[dep][i] = min(base[dep][i], tmp ^ base[dep][i]);
			base[dep][++base[dep][0]] = tmp;
		}
	}
	if(L == R) {
		int tmp = dsu_find(que[L].first).second ^ dsu_find(que[L].second).second;
		for(int i = 1; i <= base[dep][0]; ++i)
			tmp = min(tmp, tmp ^ base[dep][i]);
		que[L].first = tmp;
	} else {
		int M = (L + R) >> 1;
		memcpy(base[dep + 1], base[dep], (base[dep][0] + 1) * sizeof(int));
		solve(dep + 1, L, M);
		memcpy(base[dep + 1], base[dep], (base[dep][0] + 1) * sizeof(int));
		solve(dep + 1, M + 1, R);
	}
	while(htot > pht) {
		Pair &tmp = his[--htot];
		dsu[tmp.first] = tmp.second;
		tmp = his[--htot];
		dsu[tmp.first] = tmp.second;
		msk[tmp.first] = 0;
	}
}
int etot;
struct Edge {
	int L, R;
	Triple E;
} edges[maxn];
map<int, Pair> tim[maxn];
int main() {
	int m;
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		tim[u][v] = (Pair){qtot + 1, w};
	}
	scanf("%d", &m);
	while(m--) {
		int typ, u, v, w;
		scanf("%d%d%d", &typ, &u, &v);
		if(typ == 1) {
			scanf("%d", &w);
			tim[u][v] = (Pair){qtot + 1, w};
		} else if(typ == 2) {
			Pair tmp = tim[u][v];
			if(tmp.first <= qtot)
				edges[etot++] = (Edge){tmp.first, qtot, (Triple){(Pair){u, v}, tmp.second}};
			tim[u].erase(v);
		} else {
			que[++qtot] = (Pair){u, v};
		}
	}
	for(int i = 0; i < etot; ++i)
		update(1, qtot, edges[i].L, edges[i].R, edges[i].E);
	for(int u = 1; u <= n; ++u)
		for(map<int, Pair>::iterator it = tim[u].begin(); it != tim[u].end(); ++it) {
			int v = it -> first;
			Pair tmp = it -> second;
			if(tmp.first <= qtot)
				update(1, qtot, tmp.first, qtot, (Triple){(Pair){u, v}, tmp.second});
		}
	memset(dsu + 1, -1, n * sizeof(int));
	solve(0, 1, qtot);
	for(int i = 1; i <= qtot; ++i)
		printf("%d\n", que[i].first);
	return 0;
}
