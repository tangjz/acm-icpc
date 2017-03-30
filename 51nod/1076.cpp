#include <stdio.h>
#include <cstring>
const int maxn = 50001, maxm = 100001;
struct Edge {
	int nxt, v;
} e[maxm];
int n, m, tot, deg[maxn], lnk[maxn], pre[maxn], cnt, bcc[maxn];
bool used[maxm];
int tarjan(int u, int Fa) {
	int lowu = pre[u] = tot++;
	for(int it = lnk[u]; it != -1; it = e[it].nxt) {
		if(Fa == (it ^ 1)) continue;
		int &v = e[it].v;
		if(pre[v] == -1) {
			int lowv = tarjan(v, it);
			if(lowu > lowv) lowu = lowv;
			if(pre[u] < lowv) {
				--deg[u];
				--deg[v];
				used[it] = used[it ^ 1] = 1;
			}
		}
		else if(lowu > pre[v]) lowu = pre[v];
	}
	return lowu;
}
void dfs(int u) {
	bcc[u] = cnt;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(!used[it] && bcc[e[it].v] == -1) dfs(e[it].v);
}
void solve() {
	tot = 0, memset(pre, -1, n * sizeof(int));
	for(int i = 0; i < n; ++i)
		if(pre[i] == -1) tarjan(i, -1);
	cnt = 0, memset(bcc, -1, n * sizeof(int));
	for(int i = 0; i < n; ++i)
		if(bcc[i] == -1) dfs(i), ++cnt;
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(lnk, -1, n * sizeof(int));
	for(int i = 0; i < m; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		++deg[u];
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		++deg[v];
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	solve();
	scanf("%d", &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		puts(bcc[u] == bcc[v] ? "Yes" : "No");
	}
	return 0;
}
