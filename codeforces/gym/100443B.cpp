#include <bits/stdc++.h>
const int maxn = 301, maxm = 30001, INF = 0x3f3f3f3f;
int N, M, S, T, lev[maxn], lnk[maxn], cur[maxn];
struct Edge {
	int nxt, v, w;
} e[maxm << 1 | 1];
void addEdge(int u, int v, int w) {
	e[M] = (Edge){lnk[u], v, w};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0};
	lnk[v] = M++;
}
bool bfs() {
	int L = 0, R = 0;
	static int que[maxn];
	memset(lev, -1, N * sizeof(int));
	lev[S] = 0;
	que[R++] = S;
	while(L < R) {
		int u = que[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].w > 0 && lev[e[it].v] == -1) {
				lev[e[it].v] = lev[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return lev[T] != -1;
}
int dfs(int u, int upp) {
	if(u == T)
		return upp;
	int ret = 0, tmp;
	for(int &it = cur[u]; it != -1; it = e[it].nxt)
		if(lev[e[it].v] == lev[u] + 1 && e[it].w > 0
		&& (tmp = dfs(e[it].v, std::min(upp - ret, e[it].w))) > 0) {
			e[it].w -= tmp;
			e[it ^ 1].w += tmp;
			if((ret += tmp) == upp)
				break;
		}
	if(!ret)
		lev[u] = -1;
	return ret;
}
int dinic() {
	int flow = 0;
	while(bfs()) {
		memcpy(cur, lnk, N * sizeof(int));
		for(int tmp; (tmp = dfs(S, INF)); flow += tmp);
	}
	return flow;
}
int t, n, m, pL[maxn], pR[maxn], lim[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		N = (n << 1) + 4;
		M = 0;
		S = N - 4;
		T = N - 3;
		memset(lnk, -1, N * sizeof(int));
		for(int i = 0; i < n; ++i) {
			scanf("%d%d%d", pL + i, pR + i, lim + i);
			addEdge(S, i, INF);
			addEdge(i, n + i, INF);
			addEdge(n + i, T, INF);
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0, dt; j < n; ++j) {
				scanf("%d", &dt);
				if(i != j && pR[i] + dt < pL[j])
					addEdge(n + i, j, INF);
			}
		int SS = N - 2, TT = N - 1, MM = M;
		for(int i = 0; i < n; ++i) {
			lim[i] = (lim[i] - 1) / m + 1;
			addEdge(SS, n + i, lim[i]);
			addEdge(i, TT, lim[i]);
		}
		addEdge(T, S, INF);
		std::swap(S, SS);
		std::swap(T, TT);
		dinic();
		int flow = e[M - 1].w;
		std::swap(S, SS);
		std::swap(T, TT);
		for( ; MM < M; M -= 2) {
			int u = e[M - 1].v, v = e[M - 2].v;
			lnk[u] = e[M - 2].nxt;
			lnk[v] = e[M - 1].nxt;
		}
		std::swap(S, T);
		flow -= dinic();
		printf("Case %d: %d\n", Case, flow);
	}
	return 0;
}
