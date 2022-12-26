#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)6e5 + 1, maxd = 30, maxs = maxn * maxd + 1;
int n, m, tot, dsu[maxn], rt[maxn];
struct Trie {
	int sz, ch[2];
} e[maxs];
int tr_upd(int rt, int v, int dep) {
	int tr = rt;
	if(!rt) {
		tr = ++tot;
		e[tr] = e[rt];
	}
	++e[tr].sz;
	if(dep < maxd) {
		int o = (v >> dep) & 1;
		e[tr].ch[o] = tr_upd(e[tr].ch[o], v, dep + 1);
	}
	return tr;
}
int tr_mrg(int u, int v) {
	if(!u || !v)
		return u | v;
	e[u].sz += e[v].sz;
	e[u].ch[0] = tr_mrg(e[u].ch[0], e[v].ch[0]);
	e[u].ch[1] = tr_mrg(e[u].ch[1], e[v].ch[1]);
	return u;
}
void tr_inc(int rt) {
	for( ; rt; rt = e[rt].ch[0])
		swap(e[rt].ch[0], e[rt].ch[1]);
}
int dsu_find(int u) {
	return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		dsu[i] = -1;
		rt[i] = tr_upd(0, x, 0);
	}
	while(m--) {
		int typ, x, y, z;
		scanf("%d%d", &typ, &x);
		if(typ == 1) {
			scanf("%d", &y);
			x = dsu_find(x);
			y = dsu_find(y);
			if(x != y) {
				if(dsu[x] < dsu[y])
					swap(x, y);
				dsu[y] -= dsu[x] == dsu[y];
				dsu[x] = y;
				rt[y] = tr_mrg(rt[x], rt[y]);
			}
		} else if(typ == 2) {
			tr_inc(rt[dsu_find(x)]);
		} else {
			scanf("%d%d", &y, &z);
			x = dsu_find(x);
			int u = rt[x];
			for(int i = 0; i < y; ++i)
				u = e[u].ch[(z >> i) & 1];
			printf("%d\n", e[u].sz);
		}
	}
	return 0;
}
