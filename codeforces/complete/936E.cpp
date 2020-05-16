#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)3e5 + 1, maxd = 19;
int n, m, q, tot, ord[maxn], pre[maxn], suf[maxn], idx[maxd][maxn];
vector<int> e[maxn], g[maxn];
pair<int, int> seg[maxn], dis[maxd][maxn];
bool banE[maxn], banG[maxn];
int getRoot(int rt) {
	static int fa[maxn], sz[maxn], mx[maxn];
	tot = 0;
	fa[rt] = -1;
	ord[++tot] = rt;
	for(int i = 1; i <= tot; ++i) {
		int u = ord[i];
		sz[u] = mx[u] = 0;
		for(int &v : g[u]) {
			if(v == fa[u] || banG[v])
				continue;
			fa[v] = u;
			ord[++tot] = v;
		}
	}
	int val = tot;
	for(int i = tot; i; --i) {
		int u = ord[i];
		mx[u] = max(mx[u], tot - (++sz[u]));
		if(mx[u] < val) {
			val = mx[u];
			rt = u;
		}
		if(fa[u] != -1) {
			sz[fa[u]] += sz[u];
			mx[fa[u]] = max(mx[fa[u]], sz[u]);
		}
	}
	return rt;
}
void tree_init(int dep, int rt) {
	rt = getRoot(rt);
	int *Idx = idx[dep];
	pair<int, int> *Dis = dis[dep];
	tot = 0;
	for(int u = seg[rt].first, i = 1; u <= seg[rt].second; ++u, ++i) {
		banE[u] = 1;
		Idx[u] = rt;
		Dis[u] = make_pair(0, i);
		ord[++tot] = u;
	}
	for(int i = 1; i <= tot; ++i) {
		int u = ord[i];
		for(int &v : e[u]) {
			if(banE[v] || Idx[v])
				continue;
			Idx[v] = rt;
			Dis[v] = make_pair(Dis[u].first + 1, Dis[u].second);
			ord[++tot] = v;
		}
	}
	banG[rt] = 1;
	for(int &u : g[rt])
		if(!banG[u])
			tree_init(dep + 1, u);
}
void tree_upd(int u) {
	for(int dep = 0; dep < maxd && idx[dep][u]; ++dep) {
		int rt = idx[dep][u], len = seg[rt].second - seg[rt].first + 1;
		int *Pre = pre + seg[rt].first - 1, *Suf = suf + seg[rt].first - 1;
		int val = dis[dep][u].first, pos = dis[dep][u].second;
		for(int i = pos; i <= len; i += i & -i)
			Pre[i] = min(Pre[i], val - pos);
		for(int i = pos; i > 0; i -= i & -i)
			Suf[i] = min(Suf[i], val + pos);
	}
}
int tree_que(int u) {
	int ret = n + 1;
	for(int dep = 0; dep < maxd && idx[dep][u]; ++dep) {
		int rt = idx[dep][u], len = seg[rt].second - seg[rt].first + 1;
		int *Pre = pre + seg[rt].first - 1, *Suf = suf + seg[rt].first - 1;
		int val = dis[dep][u].first, pos = dis[dep][u].second;
		for(int i = pos; i > 0; i -= i & -i)
			ret = min(ret, val + Pre[i] + pos);
		for(int i = pos; i <= len; i += i & -i)
			ret = min(ret, val + Suf[i] - pos);
	}
	return ret;
}
pair<int, int> p[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &p[i].first, &p[i].second);
	sort(p + 1, p + n + 1);
	for(int i = 1, j; i <= n; i = j) {
		for(j = i + 1; j <= n && p[j] == make_pair(p[i].first, p[i].second + j - i); ++j) {
			e[j].push_back(j - 1);
			e[j - 1].push_back(j);
		}
		seg[++m] = make_pair(i, j - 1);
	}
	for(int i = 1, j = 1, u = 1, v = 1; i <= n; ++i) {
		pair<int, int> need = make_pair(p[i].first - 1, p[i].second);
		for( ; j < i && p[j] < need; ++j)
			v += j == seg[v].second;
		if(p[j] == need) {
			e[i].push_back(j);
			e[j].push_back(i);
			if(!g[u].size() || g[u].back() != v) {
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}
		u += i == seg[u].second;
	}
	tree_init(0, 1);
	memset(pre + 1, 0x3f, n * sizeof(int));
	memset(suf + 1, 0x3f, n * sizeof(int));
	scanf("%d", &q);
	bool upd = 0;
	while(q--) {
		int typ, x, y;
		scanf("%d%d%d", &typ, &x, &y);
		x = lower_bound(p + 1, p + n + 1, make_pair(x, y)) - p;
		if(typ == 1) {
			tree_upd(x);
			upd = 1;
		} else {
			printf("%d\n", upd ? tree_que(x) : -1);
		}
	}
	return 0;
}
