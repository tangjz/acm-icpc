#include <bits/stdc++.h>
using namespace std;
const int maxn = 3601, maxN = maxn << 1 | 1, maxM = maxn << 2 | 1, INF = 0x3f3f3f3f;
int N, M, S, T, lnk[maxN], dis[maxN], sum, flow, cost;
struct Edge {
	int nxt, v, w, c;
} e[maxM << 1 | 1];
bool vis[maxN];
void addEdge(int u, int v, int w, int c) {
	e[M] = (Edge){lnk[u], v, w, c};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0, -c};
	lnk[v] = M++;
}
bool bfs() {
	static vector<int> cand[maxn];
	memset(dis, 0x3f, N * sizeof(int));
	memset(vis, 0, N * sizeof(bool));
	int mx = dis[T] = 0;
	cand[0].push_back(T);
	for(int i = 0; i <= mx; ) {
		if(cand[i].empty()) {
			++i;
			continue;
		}
		int u = cand[i].back();
		cand[i].pop_back();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			if(!e[it ^ 1].w)
				continue;
			int v = e[it].v, tp = dis[u] + e[it ^ 1].c;
			if(tp < dis[v]) {
				dis[v] = tp;
				cand[tp].push_back(v);
				mx = max(mx, tp);
			}
		}
	}
	if(dis[S] == INF)
		return 0;
	for(int u = 0; u < N; ++u)
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			e[it].c += dis[e[it].v] - dis[u];
	sum += dis[S];
	return 1;
}
int dfs(int u, int upp) {
	if(u == T)
		return upp;
	vis[u] = 1;
	int ret = 0, tmp;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(!e[it].c && !vis[e[it].v] && e[it].w && (tmp = dfs(e[it].v, min(upp - ret, e[it].w))) > 0) {
			e[it].w -= tmp; e[it ^ 1].w += tmp;
			if((ret += tmp) == upp)
				break;
		}
	return ret;
}
int n, m, a[maxn], nxt[maxn][5], ord[maxn], f[maxn];
inline bool cmp(int const &u, int const &v) {
	return a[u] < a[v];
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx) {
			scanf("%d", a + idx);
			if(i && a[idx - m] != a[idx]) {
				int u = idx - m, v = idx;
				if(a[u] > a[v])
					swap(u, v);
				nxt[u][++nxt[u][0]] = v;
			}
			if(j && a[idx - 1] != a[idx]) {
				int u = idx - 1, v = idx;
				if(a[u] > a[v])
					swap(u, v);
				nxt[u][++nxt[u][0]] = v;
			}
			ord[idx] = idx;
		}
	n *= m;
	sort(ord, ord + n, cmp);
	for(int i = n - 1; i >= 0; --i) {
		int u = ord[i];
		f[u] = 0;
		for(int j = 1; j <= nxt[u][0]; ++j)
			f[u] = max(f[u], f[nxt[u][j]]);
		++f[u];
	}
	int ans = 0;
	N = n + n + 1;
	T = N - 1;
	for(int i = 0; i < n; ++i) {
		S = n + ord[i];
		M = flow = cost = 0;
		memset(lnk, -1, N * sizeof(int));
		for(int j = i; j < n; ++j) {
			int u = ord[j];
			dis[u] = -f[u];
			dis[n + u] = -f[u] + 1;
			addEdge(u, n + u, 1, 0);
			addEdge(n + u, T, 1, f[u] - 1);
			for(int k = 1; k <= nxt[u][0]; ++k) {
				int v = nxt[u][k];
				addEdge(n + u, v, 1, f[u] - f[v] - 1);
			}
		}
		sum = dis[S];
		dis[T] = 0;
		memset(vis, 0, N * sizeof(bool));
		int adt = dfs(S, 2);
		if(adt) {
			flow += adt;
			cost += adt * sum;
			if(adt < 2 && bfs()) {
				memset(vis, 0, N * sizeof(bool));
				adt = dfs(S, 2 - adt);
				flow += adt;
				cost += adt * sum;
			}
		}
		ans = max(ans, -cost + 1);
	}
	printf("%d\n", ans);
	return 0;
}
