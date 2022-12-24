#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int nn, n, m, tot, pre[maxn], suf[maxn], lnk[maxn], que[maxn], scc[maxn];
struct Edge {
	int nxt, v;
} e[maxn << 2 | 1];
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
	e[m] = (Edge){lnk[tot], u};
	lnk[tot] = m++;
	for(int it = suf[u]; it != -1; it = e[it].nxt)
		if(!vis[e[it].v])
			dfs2(e[it].v);
}
bool dfs3(int u) {
	vis[u] = 1;
	int mx = 0;
	for(int it = pre[u]; it != -1; it = e[it].nxt) {
		if(!vis[e[it].v] && !dfs3(e[it].v))
			return 0;
		mx = max(mx, que[e[it].v]);
	}
	for(int it = lnk[u]; it != -1; it = e[it].nxt) {
		int p = e[it].v, q = p <= nn ? p + nn : p - nn;
		if(vis[scc[q]])
			mx = max(mx, que[scc[q]] + 1);
	}
	if(mx > 1)
		return 0;
	que[u] = mx;
	return 1;
}
int main() {
	scanf("%d%d", &m, &nn);
	n = nn << 1;
	memset(pre + 1, -1, n * sizeof(int));
	memset(suf + 1, -1, n * sizeof(int));
	for(int i = 0; i < m; ++i) {
		int u, v, a, x, b, y;
		scanf("%d%d%d%d", &a, &x, &b, &y);
		u = x ? a : a + nn;
		v = y ? b + nn : b;
		e[i << 2] = (Edge){pre[u], v};
		pre[u] = i << 2;
		e[i << 2 | 1] = (Edge){suf[v], u};
		suf[v] = i << 2 | 1;
		u = y ? b : b + nn;
		v = x ? a + nn : a;
		e[i << 2 | 2] = (Edge){pre[u], v};
		pre[u] = i << 2 | 2;
		e[i << 2 | 3] = (Edge){suf[v], u};
		suf[v] = i << 2 | 3;
	}
	memset(vis + 1, 0, n * sizeof(bool));
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs1(i);
	tot = 0;
	m <<= 2;
	memset(vis + 1, 0, n * sizeof(bool));
	memset(lnk + 1, -1, n * sizeof(int));
	for(int i = n; i >= 1; --i)
		if(!vis[que[i]]) {
			++tot;
			dfs2(que[i]);
		}
	for(int i = 1; i <= nn; ++i)
		if(scc[i] == scc[i + nn]) {
			puts("IMPOSSIBLE");
			return 0;
		}
	memset(pre + 1, -1, n * sizeof(int));
	for(int i = 1; i <= n; ++i) {
		int u = scc[i];
		for(int it = suf[i]; it != -1; it = e[it].nxt) {
			int v = scc[e[it].v];
			if(u != v) {
				e[m] = (Edge){pre[u], v};
				pre[u] = m++;
			}
		}
	}
	memset(vis + 1, 0, tot * sizeof(bool));
	for(int i = 1; i <= tot; ++i)
		if(!vis[i] && !dfs3(i)) {
			puts("IMPOSSIBLE");
			return 0;
		}
	for(int i = 1; i <= nn; ++i)
		puts(que[scc[i]] ? "0" : "1");
	return 0;
}
