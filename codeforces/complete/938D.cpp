#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, int> Edge;
const int maxn = (int)2e5 + 1;
int n, m;
LL dis[maxn];
vector<Edge> e[maxn];
priority_queue<Edge> Q;
bool vis[maxn];
int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v;
		LL w;
		scanf("%d%d%lld", &u, &v, &w);
		e[u].push_back((Edge){w << 1, v});
		e[v].push_back((Edge){w << 1, u});
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", dis + i);
		Q.push((Edge){-dis[i], i});
	}
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
			int v = it -> second;
			LL tp = dis[u] + it -> first;
			if(tp < dis[v]) {
				dis[v] = tp;
				Q.push((Edge){-dis[v], v});
			}
		}
	}
	for(int i = 1; i <= n; ++i)
		printf("%lld%c", dis[i], " \n"[i == n]);
	return 0;
}
