#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 63, maxm = (int)1e4 + 1, INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, rt, f[maxn][maxn][maxn];
vector<pair<int, int> > Ref[maxn];
vector<vector<int> > e[maxn];
vector<pair<int, int> > g[maxn];
char buf[maxn];
void dijkstra(int dis[maxn]) {
	priority_queue<pair<int, int> > Q;
	static bool vis[maxn];
	memset(vis + 1, 0, m * sizeof(bool));
	for(int i = 1; i <= m; ++i)
		if(dis[i] < INF)
			Q.push(make_pair(-dis[i], i));
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		for(auto &it : g[u]) {
			int v = it.first, w = dis[u] + it.second;
			if(dis[v] > w) {
				dis[v] = w;
				Q.push(make_pair(-dis[v], v));
			}
		}
	}
}
signed main() {
	int q;
	scanf("%lld%lld", &m, &q);
	static int dis[maxn];
	static bool vis[maxn];
	memset(dis + 1, 0x3f, m * sizeof(int));
	memset(vis + 1, 0, m * sizeof(bool));
	while(q--) {
		int typ, x, y, z;
		char ch;
		vector<int> vec;
		scanf("%lld%lld", &typ, &x);
		++x;
		vec.push_back(typ);
		if(typ == 0) {
			scanf("%lld%lld", &y, &z);
			vec.push_back(++y);
			vec.push_back(++z);
			Ref[y].push_back(make_pair(x, z));
			Ref[z].push_back(make_pair(x, y));
		} else if(typ == 1) {
			scanf(" %c", &ch);
			vec.push_back((int)ch);
			dis[x] = min(dis[x], 1LL);
		} else {
			dis[x] = min(dis[x], 0LL);
		}
		e[x].push_back(vec);
	}
	priority_queue<pair<int, int> > Q;
	for(int i = 1; i <= m; ++i)
		if(dis[i] < INF)
			Q.push(make_pair(-dis[i], i));
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		for(auto &it : Ref[u]) {
			int x = it.first, v = it.second;
			if(dis[x] > dis[u] + dis[v]) {
				dis[x] = dis[u] + dis[v];
				Q.push(make_pair(-dis[x], x));
			}
		}
	}
	scanf("%lld%s", &rt, buf + 1);
	n = strlen(buf + 1);
	memset(f, 0x3f, sizeof f);
	for(int i = 1; i <= m; ++i) {
		for(int j = 1; j <= n + 1; ++j)
			f[j][j - 1][i] = min(f[j][j - 1][i], dis[i]);
		for(auto &it : e[i])
			if(it[0] == 0) {
				int u = it[1], v = it[2];
				if(dis[u] < INF)
					g[v].push_back(make_pair(i, dis[u]));
				if(dis[v] < INF)
					g[u].push_back(make_pair(i, dis[v]));
			}
	}
	for(int len = 1; len <= n; ++len)
		for(int i = 1, j = i + len - 1; j <= n; ++i, ++j) {
			static int ctr[257];
			memset(ctr, 0, sizeof ctr);
			for(int k = i; k <= j; ++k)
				++ctr[(int)buf[k]];
			for(int k = 1; k <= m; ++k)
				for(auto &it : e[k]) {
					if(it[0] == 0) {
						int lft = it[1], rht = it[2];
						for(int o = i; o < j; ++o)
							f[i][j][k] = min(f[i][j][k], f[i][o][lft] + f[o + 1][j][rht]);
					}
					if(it[0] == 1)
						f[i][j][k] = min(f[i][j][k], len - (ctr[it[1]] > 0 ? 1 : 0));
					if(it[0] == 2)
						f[i][j][k] = min(f[i][j][k], len);
				}
			dijkstra(f[i][j]);
		}
	printf("%lld\n", f[1][n][++rt]);
	return 0;
}