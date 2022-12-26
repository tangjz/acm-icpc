#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int n, m, tot, pre[maxn], suf[maxn], que[maxn], scc[maxn], f[maxn];
struct Edge {
	int nxt, v;
} e[maxn * 3];
bool vis[maxn];
void dfs1(int u) {
	vis[u] = 1;
	for(int it = pre[u]; it != -1; it = e[it].nxt)
		if(!vis[e[it].v])
			dfs1(e[it].v);
	que[++tot] = u;
}
void dfs2(int u) {
	vis[u] = 1;
	scc[u] = tot;
	++f[tot];
	for(int it = suf[u]; it != -1; it = e[it].nxt)
		if(!vis[e[it].v])
			dfs2(e[it].v);
}
void dfs3(int u) {
	vis[u] = 1;
	int mx = 0;
	for(int it = pre[u]; it != -1; it = e[it].nxt) {
		if(!vis[e[it].v])
			dfs3(e[it].v);
		mx = max(mx, f[e[it].v]);
	}
	f[u] += mx;
}
int main() {
	scanf("%d%d", &n, &m);
	memset(pre + 1, -1, n * sizeof(int));
	memset(suf + 1, -1, n * sizeof(int));
	for(int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i << 1] = (Edge){pre[u], v};
		pre[u] = i << 1;
		e[i << 1 | 1] = (Edge){suf[v], u};
		suf[v] = i << 1 | 1;
	}
	memset(vis + 1, 0, n * sizeof(bool));
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs1(i);
	tot = 0;
	memset(vis + 1, 0, n * sizeof(bool));
	for(int i = n; i >= 1; --i)
		if(!vis[que[i]]) {
			++tot;
			dfs2(que[i]);
		}
	m <<= 1;
	memset(pre + 1, -1, n * sizeof(int));
	for(int i = 1; i <= n; ++i) {
		int v = scc[i];
		for(int it = suf[i]; it != -1; it = e[it].nxt) {
			int u = scc[e[it].v];
			if(u != v) {
				e[m] = (Edge){pre[u], v};
				pre[u] = m++;
			}
		}
	}
	m = 0;
	memset(vis + 1, 0, tot * sizeof(bool));
	for(int i = 1; i <= tot; ++i) {
		if(!vis[i])
			dfs3(i);
		m = max(m, f[i]);
	}
	printf("%d\n", m);
	return 0;
}
