#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxd = 17;
int n, perm[maxn], m, lnk[maxn], idx[maxd][maxn], idx2[maxd][maxn], dis[maxd][maxn], cnt[maxn << 1 | 1];
LL sum[maxn << 1 | 1];
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
bool ban[maxn];
int tot, ord[maxn], fa[maxn], dep[maxn], sz[maxn];
void addEdge(int u, int v) {
	e[m] = (Edge){lnk[u], v};
	lnk[u] = m++;
	e[m] = (Edge){lnk[v], u};
	lnk[v] = m++;
}
void bfs(int rt) { // fa[rt], dep[rt] have been set
	tot = 0;
	ord[tot++] = rt;
	for(int i = 0; i < tot; ++i) {
		int u = ord[i];
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[v])
				continue;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			ord[tot++] = v;
		}
	}
}
int maxL;
void build(int lev, int rt) {
	if(maxL < lev)
		maxL = lev;
	fa[rt] = dep[rt] = 0;
	bfs(rt);
	int val = maxn;
	rt = -1;
	for(int i = tot - 1; i >= 0; --i) {
		int u = ord[i], mx = 0;
		sz[u] = 1;
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[v])
				continue;
			mx = max(mx, sz[v]);
			sz[u] += sz[v];
		}
		mx = max(mx, tot - sz[u]);
		if(mx < val) {
			val = mx;
			rt = u;
		}
	}
	int pid = m++;
	idx[lev][rt] = idx2[lev][rt] = pid;
	dis[lev][rt] = fa[rt] = dep[rt] = 0;
	for(int it = lnk[rt]; it != -1; it = e[it].nxt) {
		int tr = e[it].v;
		if(ban[tr])
			continue;
		fa[tr] = rt;
		dep[tr] = dep[rt] + 1;
		bfs(tr);
		int cid = m++;
		for(int i = 0; i < tot; ++i) {
			int u = ord[i];
			idx[lev][u] = pid;
			idx2[lev][u] = cid;
			dis[lev][u] = dep[u];
		}
	}
	ban[rt] = 1;
	for(int it = lnk[rt]; it != -1; it = e[it].nxt) {
		int tr = e[it].v;
		if(!ban[tr])
			build(lev + 1, tr);
	}
}
LL update(int u) {
	LL ret = 0;
	for(int i = 0; ; ++i) {
		int pid = idx[i][u], cid = idx2[i][u], tp = dis[i][u];
		ret += sum[pid] + (LL)cnt[pid] * tp;
		++cnt[pid];
		sum[pid] += tp;
		if(pid == cid)
			break;
		ret -= sum[cid] + (LL)cnt[cid] * tp;
		++cnt[cid];
		sum[cid] += tp;
	}
	return ret;
}
set<int> sp;
int lch[maxn], rch[maxn];
int main() {
	scanf("%d", &n);
	memset(lnk + 1, -1, n * sizeof(int));
	for(int i = 1; i <= n; ++i) {
		int &x = perm[i];
		scanf("%d", &x);
		if(i > 1) {
			set<int>::iterator it = sp.lower_bound(x);
			if(it != sp.end()) {
				int y = *it;
				if(!lch[y]) {
					lch[y] = x;
					addEdge(x, y);
				}
			}
			if(it != sp.begin()) {
				int y = *(--it);
				if(!rch[y]) {
					rch[y] = x;
					addEdge(x, y);
				}
			}
		}
		sp.insert(x);
	}
	m = 0;
	build(0, 1);
	LL ans = 0;
	for(int i = 1; i <= n; ++i) {
		ans += update(perm[i]);
		printf("%lld\n", ans);
	}
	return 0;
}
