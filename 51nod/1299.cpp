#include <stdio.h>
const int maxn = 100003;
int n, m, deg[maxn], lnk[maxn], f[maxn], g[maxn], h[maxn], ans;
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
bool ban[maxn];
void dfs(int u, int fa) {
	// f : jailer up
	// g : exit up
	// h : prisoner up
	int sf = 0, sg = 0, sh = 0;
	for(int it = lnk[u]; it; it = e[it].nxt) {
		int v = e[it].v;
		if(v == fa)
			continue;
		dfs(v, u);
		sf += f[v];
		sg += g[v];
		sh += h[v];
	}
	if(ban[u]) {
		ans += sg;
		h[u] = 1;
	} else if(sg && sh) {
		++ans;
		f[u] = 1;
	} else if(sg) {
		g[u] = 1;
	} else if(sh) {
		h[u] = 1;
	} else if(sf) {
		f[u] = 1;
	} else {
		g[u] = 1;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	++n;
	for(int i = 1, j = 0, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		e[++j] = (Edge){lnk[u], v};
		lnk[u] = j;
		++deg[u];
		e[++j] = (Edge){lnk[v], u};
		lnk[v] = j;
		++deg[v];
	}
	for(int i = 0, x; i < m; ++i) {
		scanf("%d", &x);
		ban[x] = 1;
	}
	for(int i = 0; i < n; ++i) {
		if(deg[i] != 1)
			continue;
		dfs(i, -1);
		if(h[i])
			++ans;
		printf("%d\n", ans <= n - m ? ans : -1);
		break;
	}
	return 0;
}
