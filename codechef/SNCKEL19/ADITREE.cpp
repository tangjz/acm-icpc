#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2.5e5 + 1;
int n, m, ord[maxn];
int lnk[maxn], dep[maxn], fa[maxn], sz[maxn];
int seq[maxn], idx[maxn], son[maxn], top[maxn];
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
void tree_build(int rt) {
	int L = 1, R = 0;
	dep[rt] = fa[rt] = 0;
	ord[++R] = rt;
	while(L <= R) {
		int u = ord[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u])
				continue;
			dep[v] = dep[u] + 1;
			fa[v] = u;
			ord[++R] = v;
		}
	}
	memset(sz + 1, 0, n * sizeof(int));
	memset(son + 1, 0, n * sizeof(int));
	++sz[rt];
	for(int i = n; i > 1; --i) {
		int u = ord[i], p = fa[u];
		sz[p] += (++sz[u]);
		if(sz[son[p]] < sz[u])
			son[p] = u;
	}
	top[rt] = rt, idx[rt] = 1;
	for(int i = 1; i <= n; ++i) {
		int u = ord[i], id = idx[u];
		seq[id++] = u;
		if(sz[u] == 1)
			continue;
		top[son[u]] = top[u];
		idx[son[u]] = id;
		id += sz[son[u]];
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || v == son[u])
				continue;
			top[v] = v;
			idx[v] = id;
			id += sz[v];
		}
	}
}
int seg[maxn << 1 | 1];
bool rev[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_upd(int L, int R, int l, int r) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r) {
		seg[rt] = R - L + 1 - seg[rt];
		rev[rt] = !rev[rt];
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(rev[rt]) {
		seg[lch] = M - L + 1 - seg[lch];
		rev[lch] = !rev[lch];
		seg[rch] = R - M - seg[rch];
		rev[rch] = !rev[rch];
		rev[rt] = 0;
	}
	if(l <= M)
		seg_upd(L, M, l, r);
	if(r > M)
		seg_upd(M + 1, R, l, r);
	seg[rt] = seg[lch] + seg[rch];
}
int main() {
	scanf("%d", &n);
	memset(lnk + 1, -1, n * sizeof(int));
	for(int i = 0; i < n - 1; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	tree_build(1);
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		for(int pu = top[u], pv = top[v]; pu != pv; u = fa[pu], pu = top[u]) {
			if(dep[pu] < dep[pv]) {
				swap(u, v);
				swap(pu, pv);
			}
			seg_upd(1, n, idx[pu], idx[u]);
		}
		if(dep[u] > dep[v])
			swap(u, v);
		if(u != v)
			seg_upd(1, n, idx[u] + 1, idx[v]);
		printf("%d\n", seg[seg_idx(1, n)]);
	}
	return 0;
}
