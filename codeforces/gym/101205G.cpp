#include <bits/stdc++.h>
using namespace std;
typedef double DB;
typedef pair<DB, int> Info;
const int maxn = 401;
int n, m, tot, lev[maxn], pcnt[maxn], dsu[maxn], dcnt[maxn];
vector<int> eq[maxn];
vector<Info> e[maxn];
struct Point {
	int x, y, z;
	int init() {
		int k;
		scanf("%d%d%d%d", &x, &y, &z, &k);
		return k;
	}
} p[maxn];
DB dis[maxn << 1 | 1];
bool can[maxn], vis[maxn << 1 | 1];
priority_queue<Info> Q;
inline int sqr(int x) {
	return x * x;
}
inline int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	dcnt[v] += dcnt[u];
	dcnt[u] = 0;
}
int main() {
	for(int Case = 1; scanf("%d%d", &n, &m) == 2; ++Case) {
		tot = 0;
		for(int i = 1; i <= n; ++i) {
			pcnt[i] = p[i].init();
			lev[tot++] = p[i].z;
		}
		sort(lev, lev + tot);
		tot = unique(lev, lev + tot) - lev;
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			eq[u].push_back(v);
			eq[v].push_back(u);
		}
		DB ans = 2e9;
		for(int o = 0; o < tot; ++o) {
			DB tmp = 0;
			for(int i = 1; i <= n; ++i)
				if((can[i] = p[i].z <= lev[o])) {
					dis[i] = dis[n + i] = 2e9;
					vis[i] = vis[n + i] = 0;
					dsu[i] = -1;
					dcnt[i] = pcnt[i];
				}
			if(!can[1] || !can[n])
				continue;
			for(int i = 1; i <= n; ++i) if(can[i])
				for(vector<int>::iterator it = eq[i].begin(); it != eq[i].end(); ++it) if(can[*it])
					dsu_merge(i, *it);
			for(int i = 1; i <= n; ++i) if(can[i] && pcnt[i])
				for(int j = i + 1; j <= n; ++j) if(can[j] && pcnt[j] && dsu_find(i) != dsu_find(j)) {
					DB dist = sqrtl(sqr(p[i].x - p[j].x) + sqr(p[i].y - p[j].y) + sqr(p[i].z - p[j].z));
					e[i].push_back(make_pair(dist - 1 + dcnt[dsu_find(j)] * 0.5, j));
					e[j].push_back(make_pair(dist - 1 + dcnt[dsu_find(i)] * 0.5, i));
				}
			dis[1] = 0.5 * dcnt[dsu_find(1)];
			Q.push(make_pair(-dis[1], 1));
			while(!Q.empty()) {
				int pu = Q.top().second;
				Q.pop();
				if(vis[pu])
					continue;
				vis[pu] = 1;
				int u = pu <= n ? pu : pu - n, uc = pu > n;
				for(vector<int>::iterator it = eq[u].begin(); it != eq[u].end(); ++it) {
					int v = *it;
					if(can[v] && dis[v] > dis[pu]) {
						dis[v] = dis[pu];
						Q.push(make_pair(-dis[v], v));
					}
				}
				if(pcnt[u] > uc)
					for(vector<Info>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
						int v = it -> second;
						DB tmp = dis[pu] + (it -> first);
						if(can[v] && pcnt[v] > 0 && dis[n + v] > tmp) {
							dis[n + v] = tmp;
							Q.push(make_pair(-dis[n + v], n + v));
						}
					}
			}
			ans = min(ans, tmp + min(dis[n], dis[n + n]));
			for(int i = 1; i <= n; ++i)
				vector<Info>().swap(e[i]);
		}
		if(ans < 1e9) {
			printf("Case %d: %.4f\n", Case, ans);
		} else {
			printf("Case %d: impossible\n", Case);
		}
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(eq[i]);
	}
	return 0;
}
