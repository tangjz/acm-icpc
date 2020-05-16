#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, ord[maxn];
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
int f[maxn];
struct Segment {
	int sum, lft, rht;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_upd(int L, int R, int x) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt] = (Segment){f[1], 1, 1};
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		seg_upd(L, M, x);
	else
		seg_upd(M + 1, R, x);
	seg[rt].sum = seg[lch].sum - f[seg[lch].rht] + seg[rch].sum - f[seg[rch].lft] + f[seg[lch].rht + seg[rch].lft];
	seg[rt].lft = seg[lch].lft + (seg[lch].lft == M - L + 1 ? seg[rch].lft : 0);
	seg[rt].rht = seg[rch].rht + (seg[rch].rht == R - M ? seg[lch].rht : 0);
}
Segment seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1;
	if(r <= M)
		return seg_que(L, M, l, r);
	if(l > M)
		return seg_que(M + 1, R, l, r);
	Segment ret = seg_que(L, M, l, r), tmp = seg_que(M + 1, R, l, r);
	ret.sum = ret.sum - f[ret.rht] + tmp.sum - f[tmp.lft] + f[ret.rht + tmp.lft];
	ret.lft = ret.lft + (ret.lft == M - max(l, L) + 1 ? tmp.lft : 0);
	ret.rht = tmp.rht + (tmp.rht == min(r, R) - M ? ret.rht : 0);
	return ret;
}
int m, etot, w[maxn], p[2][maxn];
pair<int, int> eve[maxn << 1 | 1];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; ++i)
		scanf("%d", f + i);
	memset(lnk + 1, -1, n * sizeof(int));
	for(int i = 0; i < n - 1; ++i) {
		int u, v;
		scanf("%d%d%d", &u, &v, w + i);
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	tree_build(1);
	for(int i = 0; i < n - 1; ++i) {
		int u = e[i << 1 | 1].v, v = e[i << 1].v;
		if(u == fa[v])
			swap(u, v);
		eve[etot++] = make_pair(w[i], u);
	}
	for(int i = 1; i <= m; ++i) {
		int w;
		scanf("%d%d%d", p[0] + i, p[1] + i, &w);
		eve[etot++] = make_pair(w, -i);
	}
	sort(eve, eve + etot);
	for(int i = etot - 1; i >= 0; --i)
		if(eve[i].second > 0) {
			seg_upd(1, n, idx[eve[i].second]);
		} else {
			int u = p[0][-eve[i].second], v = p[1][-eve[i].second];
			Segment su = {}, sv = {};
			for(int pu = top[u], pv = top[v]; pu != pv; u = fa[pu], pu = top[u]) {
				if(dep[pu] < dep[pv]) {
					swap(u, v);
					swap(pu, pv);
					swap(su, sv);
				}
				Segment tp = seg_que(1, n, idx[pu], idx[u]);
				su.sum = tp.sum - f[tp.rht] + su.sum - f[su.lft] + f[tp.rht + su.lft];
				su.lft = tp.lft + (tp.lft == idx[u] - idx[pu] + 1 ? su.lft : 0);
			}
			if(u != v) {
				if(dep[u] < dep[v]) {
					swap(u, v);
					swap(su, sv);
				}
				Segment tp = seg_que(1, n, idx[v] + 1, idx[u]);
				su.sum = tp.sum - f[tp.rht] + su.sum - f[su.lft] + f[tp.rht + su.lft];
				su.lft = tp.lft + (tp.lft == idx[u] - idx[v] ? su.lft : 0);
			}
			p[0][-eve[i].second] = su.sum - f[su.lft] + sv.sum - f[sv.lft] + f[su.lft + sv.lft];
		}
	for(int i = 1; i <= m; ++i)
		printf("%d\n", p[0][i]);
	return 0;
}
