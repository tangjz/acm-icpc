#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> Edge;
const int maxn = (int)2e4 + 1, maxk = 21, maxs = 1 << 19 | 1, INF = 0x3f3f3f3f;
int n, m, k, dis[maxn], msk[maxk], f[maxk][maxs], g[maxk][maxk + 2];
vector<Edge> e[maxn];
priority_queue<Edge> Q;
bool vis[maxn];
void solve(int S, int res[]) {
	for( ; !Q.empty(); Q.pop());
	memset(vis + 1, 0, n * sizeof(bool));
	memset(dis + 1, 0x3f, n * sizeof(int));
	dis[S] = 0;
	Q.push(make_pair(-dis[S], S));
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
			int v = it -> second, w = dis[u] + (it -> first);
			if(dis[v] > w) {
				dis[v] = w;
				Q.push(make_pair(-dis[v], v));
			}
		}
	}
	for(int i = 0; i < k; ++i)
		res[i] = dis[i + 2];
	res[k] = dis[1];
	res[k + 1] = dis[n];
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	while(m--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(make_pair(w, v));
		e[v].push_back(make_pair(w, u));
	}
	scanf("%d", &m);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		msk[v - 2] |= 1 << (u - 2);
	}
	if(!k) {
		solve(1, g[0]);
		printf("%d\n", g[0][k + 1]);
		return 0;
	}
	int all = 1 << (k - 1);
	for(int i = 0; i < k; ++i) {
		solve(i + 2, g[i]);
		memset(f[i], 0x3f, all * sizeof(int));
		f[i][0] = msk[i] ? INF : g[i][k];
	}
	for(int S = 0; S < all; ++S)
		for(int u = 0; u < k; ++u) {
			if(f[u][S] == INF)
				continue;
			int SS = ((S >> u) << 1 | 1) << u | (S & ((1 << u) - 1));
			for(int v = 0, o = 0; v < k; ++v) {
				if(u == v || S & (1 << o++) || (msk[v] & SS) != msk[v])
					continue;
				int T = (SS >> (v + 1)) << v | (SS & ((1 << v) - 1));
				f[v][T] = min(f[v][T], f[u][S] + g[u][v]);
			}
		}
	int ans = INF;
	for(int i = 0; i < k; ++i)
		ans = min(ans, f[i][all - 1] + g[i][k + 1]);
	printf("%d\n", ans);
	return 0;
}
