#include <cstdio>
#include <algorithm>

using std::swap;

constexpr int N = 500000;

struct Edge {int v, w; Edge *x;} *e, *lnk[N + 9], E[2 * N + 9];

void add(int u, int v, int w) {
	e->v = v, e->w = w, e->x = lnk[u], lnk[u] = e++;
}
int n, m, u, v, w, cnt, l[N + 9], r[N + 9];
int f[N + 9], s[N + 9], c[N + 9];
char opt[2];

void dfs(int fa, int u) {
	l[u] = ++cnt;
	for (Edge *p = lnk[u]; p; p = p->x)
		if (p->v != fa) {
			f[p->v] = u;
			s[p->v] = s[u] + p->w;
			dfs(u, p->v);
		}
	r[u] = cnt;
}

void add(int k, int d) {
	for (int i = k; i <= n; i += i & -i) c[i] += d;
}

int get(int k) {
	int sum = 0;
	for (int i = k; i >= 1; i -= i & -i) sum += c[i];
	return sum;
}

int main() {
	scanf("%d%d", &n, &m);
	e = E;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	dfs(0, 1);
	while (m--) {
		scanf("%s", opt);
		if (opt[0] == 'S') {
			scanf("%d%d%d", &u, &v, &w);
			if (f[u] == v)
				swap(u, v);
			int d = get(l[v]) + s[v] - get(l[u]) - s[u];
			add(l[v], w - d);
			add(r[v] + 1, d - w);
		} else if (opt[0] == 'P') {
			scanf("%d", &u);
			printf("%d\n", get(l[u]) + s[u]);
		}
	}
}

