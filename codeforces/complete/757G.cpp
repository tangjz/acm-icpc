#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)4e5 + 1, maxd = 31, maxs = (int)2e7 + 1;
int n, tot, lnk[maxn], ord[maxn], fa[maxn];
struct Edge {
	int nxt, v, w;
} e[maxn << 1 | 1];
vector<pair<int, int> > ee[maxn];
void edge_build() {
	tot = 0;
	ord[++tot] = 1;
	for(int i = 1; i <= tot; ++i) {
		int u = ord[i];
		for(auto &it : ee[u]) {
			int v = it.first;
			if(v == fa[u])
				continue;
			fa[v] = u;
			ord[++tot] = v;
		}
	}
	tot = 0;
	for(int i = 1, nn = n; i <= n; ++i) {
		int u = ord[i], p = u, j = 0, sz = ee[u].size() - (fa[u] != 0);
		for(auto &it : ee[u]) {
			int v = it.first, w = it.second;
			if(v == fa[u])
				continue;
			++j;
			if(j > 1 && j < sz) {
				++nn;
				++tot;
				e[tot << 1] = (Edge){lnk[p], nn, 0};
				lnk[p] = tot << 1;
				e[tot << 1 | 1] = (Edge){lnk[nn], p, 0};
				lnk[nn] = tot << 1 | 1;
				p = nn;
			}
			++tot;
			e[tot << 1] = (Edge){lnk[p], v, w};
			lnk[p] = tot << 1;
			e[tot << 1 | 1] = (Edge){lnk[v], p, w};
			lnk[v] = tot << 1 | 1;
		}
		vector<pair<int, int> >().swap(ee[u]);
	}
}
bool ban[maxn];
void bfs(int rt) { // fa[rt] was set
	tot = 0;
	ord[++tot] = rt;
	for(int i = 1; i <= tot; ++i) {
		int u = ord[i];
		for(int it = lnk[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[it >> 1])
				continue;
			fa[v] = u;
			ord[++tot] = v;
		}
	}
}
LL dis[maxd][maxn];
void tree_build(int dep, int rt) {
	fa[rt] = 0;
	bfs(rt);
	if(tot == 1)
		return;
	assert(dep < maxd);
	int val = tot;
	static int sz[maxn];
	for(int i = tot; i > 1; --i) {
		int u = ord[i];
		sz[u] = 1;
		for(int it = lnk[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[it >> 1])
				continue;
			sz[u] += sz[v];
		}
		int tmp = max(sz[u], tot - sz[u]);
		if(tmp < val) {
			val = tmp;
			rt = u;
		}
	}
	int lft = fa[rt], rht = rt, adt;
	for(int it = lnk[lft]; it; it = e[it].nxt) {
		int v = e[it].v;
		if(v == rht) {
			adt = e[it].w;
			ban[it >> 1] = 1;
			break;
		}
	}
	fa[lft] = 0;
	bfs(lft);
	dis[dep][lft] = -1;
	for(int i = 1; i <= tot; ++i) {
		int u = ord[i];
		for(int it = lnk[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[it >> 1])
				continue;
			dis[dep][v] = dis[dep][u] - e[it].w;
		}
	}
	fa[rht] = 0;
	bfs(rht);
	dis[dep][rht] = adt + 1;
	for(int i = 1; i <= tot; ++i) {
		int u = ord[i];
		for(int it = lnk[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[it >> 1])
				continue;
			dis[dep][v] = dis[dep][u] + e[it].w;
		}
	}
	tree_build(dep + 1, lft);
	tree_build(dep + 1, rht);
}
int q, a[maxn], rt[maxn];
struct Info {
	int lch, rch, lcnt, rcnt;
	LL lsum, rsum;
} tree[maxs];
int tree_upd(int rt, int u, int dep = 0) {
	if(dep >= maxd || !dis[dep][u])
		return rt;
	int tr = rt;
	rt = ++tot;
	tree[rt] = tree[tr];
	if(dis[dep][u] < 0) {
		++tree[rt].lcnt;
		tree[rt].lsum += -dis[dep][u] - 1;
		tree[rt].lch = tree_upd(tree[rt].lch, u, dep + 1);
	} else {
		++tree[rt].rcnt;
		tree[rt].rsum += dis[dep][u] - 1;
		tree[rt].rch = tree_upd(tree[rt].rch, u, dep + 1);
	}
	return rt;
}
LL tree_que(int rt, int u) {
	LL ret = 0;
	for(int dep = 0; rt; ++dep)
		if(dis[dep][u] < 0) {
			ret += tree[rt].rsum + tree[rt].rcnt * (-dis[dep][u] - 1LL);
			rt = tree[rt].lch;
		} else {
			ret += tree[rt].lsum + tree[rt].lcnt * (dis[dep][u] - 1LL);
			rt = tree[rt].rch;
		}
	return ret;
}
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i < n; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		ee[u].push_back(make_pair(v, w));
		ee[v].push_back(make_pair(u, w));
	}
	edge_build();
	tree_build(0, 1);
	tot = 0;
	for(int i = 1; i <= n; ++i)
		rt[i] = tree_upd(rt[i - 1], a[i]);
	while(q--) {
		int typ, x, y, z;
		static int las = 0;
		scanf("%d%d", &typ, &x);
		x ^= las;
		if(typ == 1) {
			scanf("%d%d", &y, &z);
			y ^= las;
			z ^= las;
			LL ans = tree_que(rt[y], z) - tree_que(rt[x - 1], z);
			printf("%lld\n", ans);
			las = ans & ((1 << 30) - 1);
		} else {
			swap(a[x], a[x + 1]);
			rt[x] = tree_upd(rt[x - 1], a[x]);
		}
	}
	return 0;
}
