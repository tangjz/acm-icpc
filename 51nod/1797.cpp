#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = (int)3e4 + 1, maxn2 = maxn << 1 | 1;
const int maxm = maxn2 << 4 | 1, maxb = 245, maxs = maxn2 * maxb;
int n, seq[maxn], sa[maxn], rk[maxn], ht[maxn], c[maxn];
void SuffixArray() {
	int i, j, k, *x = rk, *y = ht, m = n + 1;
	memset(c, 0, m * sizeof(int));
	for(i = 0; i < n; ++i) ++c[x[i] = seq[i]];
	for(i = 1; i < m; ++i) c[i] += c[i - 1];
	for(i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	for(k = 1; k <= n; k <<= 1, m = j) {
		j = 0;
		for(i = n - k; i < n; ++i) y[j++] = i;
		for(i = 0; i < n; ++i)
			if(sa[i] >= k) y[j++] = sa[i] - k;
		memset(c, 0, m * sizeof(int));
		for(i = 0; i < n; ++i) ++c[x[y[i]]];
		for(i = 0; i < m; ++i) c[i] += c[i - 1];
		for(i = n - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		j = 1, x[sa[0]] = 0;
		for(i = 1; i < n; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? j - 1 : j++;
		x[n] = j;
		if(j >= n) break;
	}
	for(i = 0; i < n; ++i) rk[sa[i]] = i;
	ht[0] = 0;
	for(i = k = 0; i < n; ++i) {
		if(k) --k;
		if(!rk[i]) continue;
		for(j = sa[rk[i] - 1]; seq[i + k] == seq[j + k]; ++k);
		ht[rk[i]] = k;
	}
}
int vtot, etot, lnk[maxn2], fa[maxn2], dis[maxn2], idx[maxn];
struct Edge {
	int nxt, v;
} e[maxn2];
int newNode() {
	lnk[vtot] = -1;
	fa[vtot] = dis[vtot] = 0;
	return vtot++;
}
void addEdge(int u, int v, int w) {
	fa[v] = u;
	dis[v] = dis[u] + w;
	e[etot] = (Edge){lnk[u], v};
	lnk[u] = etot++;
}
void SuffixTree() {
	vtot = etot = 0;
	int rt = newNode(), last;
	addEdge(rt, last = newNode(), n - sa[0]);
	idx[sa[0] + 1] = last;
	for(int i = 1; i < n; ++i) {
		int p = last;
		for( ; dis[p] > ht[i]; p = fa[p]);
		int dt = ht[i] - dis[p];
		if(dt > 0) {
			int q = newNode(), v = e[lnk[p]].v, w = dis[v] - dis[p];
			fa[q] = p;
			dis[q] = dis[p] + dt;
			e[lnk[p]].v = q;
			addEdge(q, v, w - dt);
			p = q;
		}
		addEdge(p, last = newNode(), n - sa[i] - ht[i]);
		idx[sa[i] + 1] = last;
	}
	for(int i = 0; i < vtot; ++i) { // reverse order
		int ctot = 0;
		c[ctot++] = -1;
		for(int it = lnk[i]; ~it; it = e[it].nxt)
			c[ctot++] = it;
		for(lnk[i] = c[--ctot]; ctot; --ctot)
			e[c[ctot]].nxt = c[ctot - 1];
	}
}
int stot, sub[maxn2], seg[maxm], lch[maxm], rch[maxm];
int seg_upd(int u, int L, int R, int x) {
	int rt = ++stot;
	lch[rt] = lch[u];
	rch[rt] = rch[u];
	seg[rt] = seg[u] + 1;
	if(L < R) {
		int M = (L + R) >> 1;
		if(x <= M)
			lch[rt] = seg_upd(lch[rt], L, M, x);
		else
			rch[rt] = seg_upd(rch[rt], M + 1, R, x);
	}
	return rt;
}
int seg_merge(int u, int v) {
	if(!u || !v)
		return u + v;
	int rt = ++stot;
	lch[rt] = seg_merge(lch[u], lch[v]);
	rch[rt] = seg_merge(rch[u], rch[v]);
	seg[rt] = seg[lch[rt]] + seg[rch[rt]];
	return rt;
}
int ptim, pseq[maxn2], pidx[maxn2];
int stim, sseq[maxn2], sidx[maxn2], sidx2[maxn2];
void dfs(int u) {
	pseq[ptim++] = u;
	pidx[u] = ptim - 1;
	sidx[u] = stim - 1;
	for(int it = lnk[u]; ~it; it = e[it].nxt) {
		int v = e[it].v;
		dfs(v);
		sub[u] = seg_merge(sub[u], sub[v]);
	}
	sseq[stim++] = u;
	sidx2[u] = stim - 1;
}
int bsize, btot, bidx[maxn2], sum[maxn + 2][maxb], ptot, pool[maxs];
int psum[maxn2][maxb], (*pcnt)[maxb] = psum, (*pref)[maxb] = psum + maxn + 1;
int ssum[maxn2][maxb], (*scnt)[maxb] = ssum, (*sref)[maxb] = ssum + maxn;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", seq + i);
	seq[n] = 0;
	SuffixArray();
	SuffixTree();
	for(int i = 1; i <= n; ++i)
		sub[idx[i]] = seg_upd(sub[idx[i]], 1, n, i);
	dfs(0);
	bsize = (int)ceil(sqrtl(vtot));
	btot = (vtot - 1) / bsize + 1;
	for(int i = bsize; i < vtot; ++i)
		bidx[i] = bidx[i - bsize] + 1;
	for(int i = 0; i < vtot; ++i) {
		for(int j = 0; j < btot; ++j) {
			psum[i][j] = i ? psum[i - 1][j] : 0;
			ssum[i][j] = i ? ssum[i - 1][j] : 0;
		}
		int u = pseq[i], x = i;
		int v = sseq[i], y = pidx[v];
		psum[i][bidx[x]] += dis[u] - dis[fa[u]];
		ssum[i][bidx[y]] += dis[v] - dis[fa[v]];
	}
	for(int i = n; i >= 1; --i) {
		int u = idx[i], x = pidx[u], y = sidx[u];
		for(int j = 0; j < btot; ++j)
			sum[i][j] = (i < n ? sum[i + 1][j] : 0) + psum[x][j] - (y >= 0 ? ssum[y][j] : 0);
	}
	memset(pool, 0, bsize * sizeof(int));
	ptot += bsize;
	for(int i = n; i >= 1; --i) {
		for(int j = 0; j < btot; ++j) {
			pcnt[i][j] = i < n ? pcnt[i + 1][j] : 0;
			scnt[i][j] = i < n ? scnt[i + 1][j] : 0;
			pref[i][j] = i < n ? pref[i + 1][j] : 0;
			sref[i][j] = i < n ? sref[i + 1][j] : 0;
		}
		int u = idx[i];
		int x = pidx[u], bx = bidx[x];
		int y = sidx[u], by = bidx[y];
		for(int j = 0; j < bx; ++j)
			++pcnt[i][j];
		memcpy(pool + ptot, pool + pref[i][bx], bsize * sizeof(int));
		pref[i][bx] = ptot;
		for(int j = 0, k = bx * bsize, *pque = pool + ptot; k <= x; ++j, ++k)
			++pque[j];
		ptot += bsize;
		if(y >= 0) {
			for(int j = 0; j < by; ++j)
				++scnt[i][j];
			memcpy(pool + ptot, pool + sref[i][by], bsize * sizeof(int));
			sref[i][by] = ptot;
			for(int j = 0, k = by * bsize, *sque = pool + ptot; k <= y; ++j, ++k)
				++sque[j];
			ptot += bsize;
		}
	}
	int q, ans = 0;
	scanf("%d", &q);
	while(q--) {
		int sta;
		LL rnk;
		scanf("%d%lld", &sta, &rnk);
		sta = (sta + ans) % n + 1;
		int pos[2];
		for(int i = 0; i < btot; ++i)
			if(rnk > sum[sta][i]) {
				rnk -= sum[sta][i];
			} else {
				for(int j = 0, k = i * bsize; j < bsize; ++j, ++k) {
					int u = pseq[k], tmp = dis[u] - dis[fa[u]];
					int y = sidx2[u], by = bidx[y], ry = y - by * bsize;
					tmp *= pcnt[sta][i] + pool[pref[sta][i] + j] - scnt[sta][by] - pool[sref[sta][by] + ry];
					if(rnk > tmp) {
						rnk -= tmp;
					} else {
						pos[0] = u;
						break;
					}
				}
				break;
			}
		int L = 1, R = n, adt = 0;
		pos[1] = sub[pos[0]];
		while(L < R) {
			int M = (L + R) >> 1;
			if(sta <= M) {
				pos[1] = lch[pos[1]];
				R = M;
			} else {
				adt += seg[lch[pos[1]]];
				pos[1] = rch[pos[1]];
				L = M + 1;
			}
		}
		if(L < sta)
			adt += seg[pos[1]];
		int rem = seg[sub[pos[0]]] - adt;
		int len = (rnk - 1) / rem + 1;
		rnk = rnk - (len - 1LL) * rem + adt;
		L = 1, R = n;
		pos[1] = sub[pos[0]];
		while(L < R) {
			int M = (L + R) >> 1;
			LL cnt = seg[lch[pos[1]]];
			if(rnk <= cnt) {
				pos[1] = lch[pos[1]];
				R = M;
			} else {
				rnk -= cnt;
				pos[1] = rch[pos[1]];
				L = M + 1;
			}
		}
		printf("%d %d\n", ans = L, L + dis[fa[pos[0]]] + len - 1);
	}
	return 0;
}
