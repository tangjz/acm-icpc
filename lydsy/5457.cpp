#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)4e5 + 1;
int n, ord[maxn], lnk[maxn], dep[maxn], fa[maxn], sz[maxn];
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
int m, a[maxn], b[maxn], cnt[maxn], stk[maxn];
pair<int, int> mx, ans[maxn];
void counter_clear() {
	for( ; m > 0; --m)
		cnt[stk[m - 1]] = 0;
	mx = make_pair(0, -1);
}
void counter_update(int x, int y) {
	if(!cnt[x])
		stk[m++] = x;
	pair<int, int> tmp = make_pair(cnt[x] += y, -x);
	if(mx < tmp)
		mx = tmp;
}
int main() {
	scanf("%d%*d", &n);
	memset(lnk + 1, -1, n * sizeof(int));
	for(int i = 0; i < n - 1; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", a + i, b + i);
	tree_build(1);
	counter_clear();
	for(int i = n; i >= 1; --i) {
		int u = seq[i];
		if(sz[u] > 1)
			for(int L = i + sz[son[u]] + 1, R = i + sz[u]; L < R; ++L)
				counter_update(a[seq[L]], b[seq[L]]);
		counter_update(a[u], b[u]);
		ans[u] = mx;
		if(i > 1 && son[fa[u]] != u)
			counter_clear();
	}
	for(int i = 1; i <= n; ++i)
		printf("%d %d\n", -ans[i].second, ans[i].first);
	return 0;
}
