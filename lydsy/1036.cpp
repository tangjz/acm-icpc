#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)3e4 + 1, INF = 0x3f3f3f3f;
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
	top[rt] = idx[rt] = 1;
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
struct Seg {
	int max, sum;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_upd(int L, int R, int x, int v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt] = (Seg){v, v};
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		seg_upd(L, M, x, v);
	else
		seg_upd(M + 1, R, x, v);
	seg[rt].max = max(seg[lch].max, seg[rch].max);
	seg[rt].sum = seg[lch].sum + seg[rch].sum;
}
Seg seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1;
	if(r <= M)
		return seg_que(L, M, l, r);
	if(M < l)
		return seg_que(M + 1, R, l, r);
	Seg sL = seg_que(L, M, l, r), sR = seg_que(M + 1, R, l, r);
	return (Seg){max(sL.max, sR.max), sL.sum + sR.sum};
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
	for(int i = 1; i <= n; ++i) {
		int w;
		scanf("%d", &w);
		seg_upd(1, n, idx[i], w);
	}
	scanf("%d", &m);
	while(m--) {
		int u, v;
		char buf[7];
		scanf("%s%d%d", buf, &u, &v);
		if(buf[0] == 'C') {
			seg_upd(1, n, idx[u], v);
		} else {
			Seg ret = (Seg){-INF, 0}, tmp;
			for(int pu = top[u], pv = top[v]; pu != pv; u = fa[pu], pu = top[u]) {
				if(dep[pu] < dep[pv]) {
					swap(u, v);
					swap(pu, pv);
				}
				tmp = seg_que(1, n, idx[pu], idx[u]);
				ret = (Seg){max(ret.max, tmp.max), ret.sum + tmp.sum};
			}
			if(dep[u] > dep[v])
				swap(u, v);
			tmp = seg_que(1, n, idx[u], idx[v]);
			ret = (Seg){max(ret.max, tmp.max), ret.sum + tmp.sum};
			printf("%d\n", buf[1] == 'M' ? ret.max : ret.sum);
		}
	}
	return 0;
}
