#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = 998244353;
map<vector<int>, int> Hash;
int n, m, deg[maxn];
pair<int, int> e[maxn][3];
bool vis[maxn];
inline void addEdge(int u, int v, int c) {
	for(int i = 0; i < deg[u]; ++i)
		if(e[u][i].first == v) {
			e[u][i].second |= c;
			return;
		}
	e[u][deg[u]++] = make_pair(v, c);
}
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		int m0, m1;
		scanf("%d%d%d", &n, &m0, &m1);
		for(int i = 1; i <= n; ++i)
			deg[i] = vis[i] = 0;
		while(m0--) {
			int u, v;
			scanf("%d%d", &u, &v);
			addEdge(u, v, 1);
			addEdge(v, u, 1);
		}
		while(m1--) {
			int u, v;
			scanf("%d%d", &u, &v);
			addEdge(u, v, 2);
			addEdge(v, u, 2);
		}
		m = 0;
		Hash.clear();
		for(int i = 1; i <= n; ++i) {
			if(!deg[i]) {
				vis[i] = 1;
				++m;
			}
			if(vis[i])
				continue;
			vector<int> col, rep;
			auto walk = [&](int u, int las) {
				while(!vis[u]) {
					vis[u] = 1;
					int v = -1;
					for(int i = 0; i < deg[u]; ++i)
						if(e[u][i].first != las) {
							col.push_back(e[u][i].second);
							v = e[u][i].first;
							break;
						}
					if(v == -1)
						break;
					las = u;
					u = v;
				}
				return u;
			};
			if(walk(i, 0) == i) { // circle
				rep.push_back((int)col.size());
			} else { // 2-circle or chain
				if(deg[i] == 2) {
					reverse(col.begin(), col.end());
					vis[i] = 0;
					walk(i, vis[e[i][0].first] ? e[i][0].first : e[i][1].first);
				}
				if(col.front() == 3) {
					rep.push_back(2);
				} else {
					int x = col.front(), y = col.back();
					if(x > y)
						swap(x, y);
					rep.push_back((int)col.size());
					rep.push_back(x);
					rep.push_back(y);
				}
			}
			map<vector<int>, int>::iterator it = Hash.find(rep);
			if(it != Hash.end()) {
				++(it -> second);
			} else {
				Hash.insert(make_pair(rep, 1));
			}
		}
		int ans = 1;
		for(int i = 2; i <= m; ++i)
			ans = (LL)ans * i % mod;
		for(auto &it : Hash) {
			auto &jt = it.first;
			int ways = (int)jt.size() > 1 ? (jt[1] == jt[2] ? 2 : 1) : jt[0], cnt = it.second;
			for(int i = 1; i <= cnt; ++i)
				ans = (LL)ans * ways % mod * i % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
