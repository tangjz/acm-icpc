#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 500001, maxq = 100001, maxd = 19;
int n, q, qtot, que[maxn], tot, in[maxn], out[maxn], dep[maxn], fa[maxd][maxn];
int ord[maxq], tmp[maxq], st, tim[maxn], bit[maxn], res[maxq];
vector<int> e[maxn];
struct Query {
	int typ, a, b, c, d;
	// 1: add coin [c] to path from [a] to [b], where the lca of [a] and [b] is [d]
	// 2: query [d]-th smallest coin added from day [b] to day [c] at vertex [a]
} query[maxq];
struct Event {
	int tim, idx;
	bool operator < (Event const &t) const {
		return tim < t.tim || (tim == t.tim && query[idx].typ < query[t.idx].typ);
	}
} event[maxq << 1 | 1];
void dfs(int u) {
	in[u] = ++tot;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(v == fa[0][u])
			continue;
		dep[v] = dep[u] + 1;
		fa[0][v] = u;
		dfs(v);
	}
	out[u] = tot;
}
int lca(int u, int v) {
	for(int i = 0, j = dep[u] - dep[v]; j > 0; ++i, j >>= 1)
		(j & 1) && (u = fa[i][u]);
	for(int i = 0, j = dep[v] - dep[u]; j > 0; ++i, j >>= 1)
		(j & 1) && (v = fa[i][v]);
	if(u == v)
		return u;
	for(int i = maxd - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
void bit_add(int x, int v) {
	for( ; x <= n; x += x & -x) {
		if(tim[x] != st) {
			tim[x] = st;
			bit[x] = 0;
		}
		bit[x] += v;
	}
}
int bit_sum(int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		if(tim[x] == st)
			ret += bit[x];
	return ret;
}
#include <cassert>
void solve(int L, int R, int qL, int qR) {
	if(L > R) // || qL > qR
		return;
	if(qL == qR) {
		for( ; L <= R; ++L) {
			int o = ord[L];
			if(query[o].typ == 2)
				res[o] = que[qL];
		}
		return;
	}
	int qM = (qL + qR) >> 1;
	tot = 0;
	for(int i = L; i <= R; ++i) {
		int o = ord[i];
		Query &cur = query[o];
		if(cur.typ == 1) {
			if(cur.c <= qM)
				event[++tot] = (Event){o, o};
		} else {
			event[++tot] = (Event){cur.b - 1, o};
			event[++tot] = (Event){cur.c, o};
		}
	}
	sort(event + 1, event + tot + 1);
	++st;
	for(int i = 1; i <= tot; ++i) {
		Event &curE = event[i];
		Query &curQ = query[curE.idx];
		if(curQ.typ == 1) {
			bit_add(in[curQ.a], 1);
			bit_add(in[curQ.b], 1);
			bit_add(in[curQ.d], -1);
			if(fa[0][curQ.d])
				bit_add(in[fa[0][curQ.d]], -1);
		} else if(curE.tim < curQ.b) {
			res[curE.idx] = bit_sum(out[curQ.a]) - bit_sum(in[curQ.a] - 1);
		} else {
			res[curE.idx] = bit_sum(out[curQ.a]) - bit_sum(in[curQ.a] - 1) - res[curE.idx];
		}
	}
	int M = L - 1, len = 0;
	for(int i = L; i <= R; ++i) {
		int o = ord[i];
		Query &cur = query[o];
		if(cur.typ == 1) {
			if(cur.c <= qM)
				ord[++M] = o;
			else
				tmp[++len] = o;
		} else {
			if(res[o] < cur.d) {
				cur.d -= res[o];
				tmp[++len] = o;
				assert(cur.d >= 1);
			} else {
				ord[++M] = o;
			}
		}
	}
	memcpy(ord + M + 1, tmp + 1, len * sizeof(int));
	solve(L, M, qL, qM);
	solve(M + 1, R, qM + 1, qR);
}
int main() {
	while(scanf("%d", &n) == 1) {
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		scanf("%d", &q);
		qtot = 0;
		for(int i = 1; i <= q; ++i) {
			Query &cur = query[i];
			scanf("%d%d%d%d", &cur.typ, &cur.a, &cur.b, &cur.c);
			if(cur.typ == 1) {
				que[++qtot] = cur.c;
			} else {
				scanf("%d", &cur.d);
			}
		}
		sort(que + 1, que + qtot + 1);
		qtot = unique(que + 1, que + qtot + 1) - que - 1;
		tot = dep[1] = fa[0][1] = 0;
		dfs(1);
		for(int i = 1; i < maxd; ++i)
			for(int j = 1; j <= n; ++j)
				fa[i][j] = fa[i - 1][fa[i - 1][j]];
		tot = 0;
		for(int i = 1; i <= q; ++i) {
			Query &cur = query[i];
			if(cur.typ == 1) {
				event[++tot] = (Event){i, i};
				cur.c = lower_bound(que + 1, que + qtot + 1, cur.c) - que;
				cur.d = lca(cur.a, cur.b);
			} else {
				event[++tot] = (Event){cur.b - 1, i};
				event[++tot] = (Event){cur.c, i};
			}
		}
		sort(event + 1, event + tot + 1);
		++st;
		for(int i = 1; i <= tot; ++i) {
			Event &curE = event[i];
			Query &curQ = query[curE.idx];
			if(curQ.typ == 1) {
				bit_add(in[curQ.a], 1);
				bit_add(in[curQ.b], 1);
				bit_add(in[curQ.d], -1);
				if(fa[0][curQ.d])
					bit_add(in[fa[0][curQ.d]], -1);
			} else if(curE.tim < curQ.b) {
				res[curE.idx] = bit_sum(out[curQ.a]) - bit_sum(in[curQ.a] - 1);
			} else {
				res[curE.idx] = bit_sum(out[curQ.a]) - bit_sum(in[curQ.a] - 1) - res[curE.idx];
			}
		}
		tot = 0;
		for(int i = 1; i <= q; ++i)
			if(query[i].typ == 2 && res[i] < query[i].d) {
				res[i] = -1;
			} else {
				ord[++tot] = i;
			}
		solve(1, tot, 1, qtot);
		for(int i = 1; i <= q; ++i)
			if(query[i].typ == 2)
				printf("%d\n", res[i]);
	}
	return 0;
}
