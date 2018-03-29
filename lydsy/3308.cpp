#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1, maxm = (int)2e5 + 1, INF = 0x3f3f3f3f;
namespace PrimDual {
	int N, M, S, T, lnk[maxn], dis[maxn], sum, flow, cost;
	struct Edge {
		int nxt, v, w;
		int c;
	} e[maxm << 1 | 1];
	bool vis[maxn];
	inline void addEdge(int u, int v, int w, int c) {
		e[M] = (Edge){lnk[u], v, w, c};
		lnk[u] = M++;
		e[M] = (Edge){lnk[v], u, 0, -c};
		lnk[v] = M++;
	}
	bool SPFA() {
		int L = 0, R = 0;
		static int que[maxn];
		memset(dis, 0x3f, N * sizeof(int));
		memset(vis, 0, N * sizeof(int));
		dis[T] = 0;
		vis[T] = 1;
		que[R++] = T;
		while(L != R) {
			int u = que[L++];
			vis[u] = 0;
			L == maxn && (L = 0);
			for(int it = lnk[u]; it != -1; it = e[it].nxt) {
				if(!e[it ^ 1].w)
					continue;
				int v = e[it].v, tp = dis[u] + e[it ^ 1].c;
				if(tp < dis[v]) {
					dis[v] = tp;
					if(!vis[v]) {
						vis[v] = 1;
						que[R++] = v;
						R == maxn && (R = 0);
					}
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
	bool Dijkstra() {
		priority_queue<pair<int, int> > Q;
		memset(dis, 0x3f, N * sizeof(int));
		memset(vis, 0, N * sizeof(int));
		dis[T] = 0;
		Q.push(make_pair(-dis[T], T));
		while(!Q.empty()) {
			int u = Q.top().second;
			Q.pop();
			if(vis[u])
				continue;
			vis[u] = 1;
			for(int it = lnk[u]; it != -1; it = e[it].nxt) {
				if(!e[it ^ 1].w)
					continue;
				int v = e[it].v, tp = dis[u] + e[it ^ 1].c;
				if(tp < dis[v]) {
					dis[v] = tp;
					Q.push(make_pair(-dis[v], v));
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
			if(!e[it].c && !vis[e[it].v] && e[it].w
			&& (tmp = dfs(e[it].v, min(upp - ret, e[it].w))) > 0) {
				e[it].w -= tmp;
				e[it ^ 1].w += tmp;
				if((ret += tmp) == upp)
					break;
			}
		return ret;
	}
	void minCost(int upp = ~0u >> 1) {
		SPFA();
		do
			while(upp > 0) {
				memset(vis, 0, N * sizeof(bool));
				int adt = dfs(S, upp);
				if(!adt)
					break;
				upp -= adt;
				flow += adt;
				cost += adt * sum;
			}
		while(Dijkstra() && sum < 0);
	}
	void solve() {
		int n, tot = 0;
		static int pr[maxn], d[maxn] = {};
		scanf("%d", &n);
		for(int i = 2; i <= n; ++i) {
			if(!d[i])
				pr[tot++] = d[i] = i;
			for(int j = 0, k; (k = i * pr[j]) <= n; ++j) {
				d[k] = pr[j];
				if(d[i] == pr[j])
					break;
			}
		}
		pr[tot] = n + 1;
		for( ; tot && pr[tot - 1] * pr[0] > n; --tot);
		N = tot + 2;
		S = N - 2;
		T = N - 1;
		M = sum = flow = cost = 0;
		memset(lnk, -1, N * sizeof(int));
		for(tot = 0; pr[tot] * pr[tot] <= n; ++tot) {
			addEdge(S, tot, 1, 0);
			for( ; d[pr[tot]] * pr[tot] <= n; d[pr[tot]] *= pr[tot]);
			cost -= d[pr[tot]];
		}
		for( ; pr[tot] * pr[0] <= n; ++tot) {
			addEdge(tot, T, 1, 0);
			cost -= pr[tot];
			for(int i = 0, lim = n / pr[tot]; pr[i] <= lim; ++i) {
				int cst = pr[i];
				for( ; cst * pr[i] <= lim; cst *= pr[i]);
				cst = cst * pr[tot] - d[pr[i]] - pr[tot];
				if(cst > 0)
					addEdge(i, tot, 1, -cst);
			}
		}
		minCost(); // without max flow
		for(cost -= 1; pr[tot] <= n; cost -= pr[tot++]);
		printf("%d\n", -cost);
	}
}
int main() {
	PrimDual::solve();
	return 0;
}
