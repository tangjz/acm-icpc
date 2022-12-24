#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = (int)5e4 + 1, maxm = (int)1e5 + 1, maxd = 17, maxs = maxm * maxd;
int n, m, tot, a[maxn], pre[maxn], suf[maxn], fa[maxn], ord[maxn], rnk[maxn];
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
int *seq = pre, *in = rnk, *out = suf, *dep = dsu, *sz = pos, *top = idom, *son = sdom;
void bfs(int rt) { // fa, ord
	dep[rt] = 0;
	fa[rt] = -1;
	ord[0] = rt;
	for(int i = 0, otot = 1; i < otot; ++i) {
		int u = ord[i];
		sz[u] = 1;
		son[u] = -1;
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			dep[v] = dep[u] + 1;
			fa[v] = u;
			ord[otot++] = v;
		}
	}
	for(int i = n - 1; i > 0; --i) {
		int u = ord[i], p = fa[u];
		sz[p] += sz[u];
		if(son[p] == -1 || sz[son[p]] < sz[u])
			son[p] = u;
	}
	top[rt] = rt;
	in[rt] = 0;
	for(int i = 0; i < n; ++i) {
		int u = ord[i], idx = in[u];
		seq[idx++] = u;
		if(son[u] != -1) {
			top[son[u]] = top[u];
			in[son[u]] = idx;
			idx += sz[son[u]];
		}
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			if(v == son[u])
				continue;
			top[v] = v;
			in[v] = idx;
			idx += sz[v];
		}
		out[u] = idx - 1;
	}
}
int lca(int u, int v) {
	for( ; top[u] != top[v]; u = fa[top[u]])
		if(dep[top[u]] < dep[top[v]])
			swap(u, v);
	return dep[u] < dep[v] ? u : v;
}
struct Segment {
	int sz, sum, tag;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_build(int L, int R) {
	Segment &rt = seg[seg_idx(L, R)];
	rt.sz = R - L + 1;
	if(L == R) {
		rt.sum = a[seq[L]];
	} else {
		int M = (L + R) >> 1;
		seg_build(L, M);
		seg_build(M + 1, R);
		rt.sum = seg[seg_idx(L, M)].sum + seg[seg_idx(M + 1, R)].sum;
	}
}
void seg_upd(int L, int R, int l, int r, int v) {
	Segment &rt = seg[seg_idx(L, R)];
	if(l <= L && R <= r) {
		rt.sum += rt.sz * v;
		rt.tag += v;
	} else {
		int M = (L + R) >> 1;
		Segment &lch = seg[seg_idx(L, M)];
		Segment &rch = seg[seg_idx(M + 1, R)];
		if(rt.tag) {
			lch.sum += lch.sz * rt.tag;
			lch.tag += rt.tag;
			rch.sum += rch.sz * rt.tag;
			rch.tag += rt.tag;
			rt.tag = 0;
		}
		if(l <= M)
			seg_upd(L, M, l, r, v);
		if(M < r)
			seg_upd(M + 1, R, l, r, v);
		rt.sum = lch.sum + rch.sum;
	}
}
int seg_que(int L, int R, int l, int r) {
	int ret = 0;
	Segment &rt = seg[seg_idx(L, R)];
	if(l <= L && R <= r) {
		ret = rt.sum;
	} else {
		int M = (L + R) >> 1;
		Segment &lch = seg[seg_idx(L, M)];
		Segment &rch = seg[seg_idx(M + 1, R)];
		if(rt.tag) {
			lch.sum += lch.sz * rt.tag;
			lch.tag += rt.tag;
			rch.sum += rch.sz * rt.tag;
			rch.tag += rt.tag;
			rt.tag = 0;
		}
		if(l <= M)
			ret += seg_que(L, M, l, r);
		if(M < r)
			ret += seg_que(M + 1, R, l, r);
		rt.sum = lch.sum + rch.sum;
	}
	return ret;
}
int qtim, qtot;
struct Operation {
	int tim, L, R, v;
} que[maxs];
void update(int typ, int x, int y) {
	if(typ == 1) {
		seg_upd(0, n - 1, in[x], in[x], y);
		que[qtot++] = (Operation){qtim, in[x], in[x], y};
	} else if(typ == 2) {
		seg_upd(0, n - 1, in[x], out[x], y);
		que[qtot++] = (Operation){qtim, in[x], out[x], y};
	} else {
		for( ; x != -1; x = fa[top[x]]) {
			seg_upd(0, n - 1, in[top[x]], in[x], y);
			que[qtot++] = (Operation){qtim, in[top[x]], in[x], y};
		}
	}
}
int query(int typ, int x) {
	int ret = 0;
	if(typ == 1) {
		ret += seg_que(0, n - 1, in[x], out[x]);
	} else if(typ == 2) {
		for( ; x != -1; x = fa[top[x]])
			ret += seg_que(0, n - 1, in[top[x]], in[x]);
	} else {
		int c = ++x, scnt = 0, stop = 0;
		static int sp[maxn], stk[maxn], up[maxn], down[maxn];
		for(int i = 0; i < c; ++i) {
			scanf("%d", &x);
			if(--x)
				sp[scnt++] = x;
		}
		sort(sp, sp + scnt, cmp);
		c = scnt = unique(sp, sp + scnt) - sp;
		up[0] = down[0] = -1;
		sp[scnt++] = 0;
		stk[stop++] = 0;
		m = 0;
		for(int i = 0; i < c; ++i) {
			int u = sp[i], pp = lca(u, stk[stop - 1]);
			for( ; dep[pp] < dep[stk[stop - 1]]; --stop);
			int p = stk[stop - 1];
			if(dep[p] < dep[pp]) {
				int v = down[p];
				down[p] = pp;
				up[pp] = p;
				down[pp] = v;
				up[v] = pp;
				sp[scnt++] = p = pp;
				stk[stop++] = p;
			}
			down[p] = u;
			up[u] = p;
			stk[stop++] = u;
		}
		for(int i = 0; i < scnt; ++i) {
			int u = sp[i], low = up[u] == -1 ? 0 : dep[up[u]] + 1;
			for( ; dep[top[u]] > low; u = fa[top[u]])
				ret += seg_que(0, n - 1, in[top[u]], in[u]);
			ret += seg_que(0, n - 1, in[u] - (dep[u] - low), in[u]);
		}
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		pre[i] = suf[i] = lnk[i] = rnk[i] = -1;
		dsu[i] = pos[i] = sdom[i] = i;
		scanf("%d", a + i);
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
	m = 0;
	for(int i = 0; i < n; ++i) {
		int u = ord[i];
		lnk[u] = -1;
		if(cmp(idom[u], u)) {
			e[m] = (Edge){lnk[idom[u]], u};
			lnk[idom[u]] = m++;
		}
	}
	bfs(0);
	seg_build(0, n - 1);
	scanf("%d", &tot);
	while(tot--) {
		char op[3];
		int typ, x, y;
		scanf("%s%d", op, &typ);
		if(op[0] == 'C') {
			scanf("%d%d", &x, &y);
			update(typ, --x, y);
			++qtim;
		} else if(op[0] == 'Q') {
			scanf("%d", &x);
			printf("%d\n", query(typ, --x));
		} else {
			(qtim -= typ) < 0 && (qtim = 0);
			for( ; qtot && que[qtot - 1].tim >= qtim; --qtot)
				seg_upd(0, n - 1, que[qtot - 1].L, que[qtot - 1].R, -que[qtot - 1].v);
		}
	}
	return 0;
}
