#include <bits/stdc++.h>
using namespace std;
const int maxm = 4001, INF = 0x3f3f3f3f;
int t, n, m, lnk[maxm], dis[maxm], ans;
struct Edge {
	int nxt, v, w;
} e[maxm << 1 | 1];
bool vis[maxm];
priority_queue<pair<int, int> > Q;
map<pair<int, int>, int> Hash;
inline int getID(int x, int y) {
	pair<int, int> state = make_pair(x, y);
	if(Hash.count(state))
		return Hash[state];
	lnk[n] = -1;
	return Hash[state] = n++;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		n = 0;
		map<pair<int, int>, int>().swap(Hash);
		scanf("%d", &m);
		for(int i = 0; i < m; ++i) {
			int x1, y1, x2, y2, u, v, w;
			scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &w);
			u = getID(x1, y1);
			v = getID(x2, y2);
			e[i << 1] = (Edge){lnk[u], v, w};
			lnk[u] = i << 1;
			e[i << 1 | 1] = (Edge){lnk[v], u, w};
			lnk[v] = i << 1 | 1;
		}
		ans = INF;
		for(int i = 0; i < m; ++i) {
			for( ; !Q.empty(); Q.pop());
			memset(vis, 0, n * sizeof(bool));
			memset(dis, 0x3f, n * sizeof(int));
			int S = e[i << 1 | 1].v, T = e[i << 1].v, DT = e[i << 1].w;
			Q.push(make_pair(-(dis[S] = 0), S));
			while(!Q.empty()) {
				int u = Q.top().second;
				Q.pop();
				if(vis[u])
					continue;
				vis[u] = 1;
				if(u == T || dis[u] + DT >= ans)
					break;
				for(int it = lnk[u]; it != -1; it = e[it].nxt) {
					if((it >> 1) == i)
						continue;
					int v = e[it].v, tmp = dis[u] + e[it].w;
					if(tmp < dis[v]) {
						dis[v] = tmp;
						Q.push(make_pair(-dis[v], v));
					}
				}
			}
			ans = min(ans, dis[T] + DT);
		}
		printf("Case #%d: %d\n", Case, ans < INF ? ans : 0);
	}
	return 0;
}
