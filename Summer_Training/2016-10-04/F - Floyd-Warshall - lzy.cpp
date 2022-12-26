#include <cctype>
#include <cstdio>
#include <algorithm>

#define N 100000
#define M 100200

using namespace std;

const int inf = 0x3fffffff;

struct Edge {int v; Edge *x;} *lnk[N + 9], *e, E[2 * M + 9];

int n, m, q, u, v;
int d[N + 9];
int f[19][N + 9];
bool vis[N + 9];
int tot, key[N + 9], s[209][N + 9];
int l, r, que[N + 9];
pair<int, int> g[M + 9];

inline
void add(int u, int v) {
	*e = (Edge){v, lnk[u]};
	lnk[u] = e++;
}

void dfs(int fa, int u) {
	vis[u] = true;
	f[0][u] = fa;
	for (int i = 1; i < 19; ++i) f[i][u] = f[i - 1][f[i - 1][u]];
	for (Edge *p = lnk[u]; p; p = p->x) {
		if (p->v == fa) continue;
		if (vis[p->v]) {
			key[tot++] = u;
			key[tot++] = p->v;
		}
		else {
			d[p->v] = d[u] + 1;
			dfs(u, p->v);
		}
	}
}

void bfs(int u, int s[]) {
	for (int i = 1; i <= n; ++i) vis[i] = false;
	s[u] = 0;
	vis[que[(r = 0)++] = u] = true;
	for (l = 0; l < r; ++l) {
		u = que[l];
		for (Edge *p = lnk[u]; p; p = p->x)
			if (!vis[p->v]) {
				s[p->v] = s[u] + 1;
				vis[que[r++] = p->v] = true;
			}
	}
}

inline
int lca(int u, int v) {
	if (d[u] > d[v]) swap(u, v);
	int det = d[v] - d[u];
	for (int i = 0; i < 19; ++i)
		if (det & 1 << i) v = f[i][v];
	for (int i = 18; i >= 0; --i) {
		if (f[i][u] != f[i][v]) {
			u = f[i][u];
			v = f[i][v];
		}
	}
	if (u != v) u = f[0][u];
	return u;
}

inline
int alice(int u, int v) {
	int a = lca(u, v);
	//printf("lca: %d %d %d\n", u, v, a);
	//printf("lca: %d %d %d\n", d[u], d[v], d[a]);
	return d[u] - d[a] + d[v] - d[a];
}

inline
int bob(int u, int v) {
	int ret = inf;
	for (int i = 0; i < tot; ++i)
		ret = min(ret, s[i][u] + s[i][v]);
	return ret;
}

//~ void get(int &x) {
	//~ int c;
	//~ while (!isdigit(c = getchar()));
	//~ x = c - '0';
	//~ while (isdigit(c = getchar())) x = x * 10 + c - '0';
//~ }

int main() {
	//get(n);
	//get(m);
	//get(q);
	scanf("%d%d%d", &n, &m, &q);
	while (m--) {
		//get(u), get(v);
		scanf("%d%d", &u, &v);
		if (u != v) {
			if (u > v) swap(u, v);
			g[tot++] = make_pair(u, v);
		}
	}
	tot = unique(g, g + tot) - g;
	e = E;
	for (int i = 0; i < tot; ++i) {
		u = g[i].first, v = g[i].second;
		add(u, v);
		add(v, u);
	}
	tot = 0;
	
	dfs(0, 1);
	sort(key, key + tot);
	tot = unique(key, key + tot) - key;
	for (int i = 0; i < tot; ++i)
		bfs(key[i], s[i]);
	while (q--) {
		//get(u), get(v);
		scanf("%d%d", &u, &v);
		printf("%d\n", min(alice(u, v), bob(u, v)));
	}
	return 0;
}
