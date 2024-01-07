#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)1e5 + 1, mod = 998244353;
int Hash0;
map<vector<int>, pair<int, int> > Hash1, Hash2;
int n, deg[maxn], typ[maxn];
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
		Hash0 = 0;
		Hash1.clear();
		Hash2.clear();
		for(int i = 1; i <= n; ++i) {
			if(!deg[i]) {
				vis[i] = 1;
				++Hash0;
			}
			if(vis[i])
				continue;
			vector<int> col;
			int u, las = 0;
			for(u = i; !vis[u]; ) {
				vis[u] = 1;
				int v = -1;
				for(int i = 0; i < deg[u]; ++i) {
					int w = e[u][i].first;
					if(w != las) {
						col.push_back(e[u][i].second);
						v = w;
						break;
					}
				}
				if(v == -1)
					break;
				las = u;
				u = v;
			}
			auto cmp = [](vector<int> const &u, vector<int> const &v) {
				if(u.size() != v.size())
					return (int)u.size() - (int)v.size();
				int len = (int)u.size();
				vector<int>::const_iterator it = u.begin(), jt = v.begin();
				for(int i = 0; i < len; ++i) {
					int diff = *(it++) - *(jt++);
					if(diff != 0)
						return diff;
				}
				return 0;
			};
			if(u == i) { // circle
				auto get_min_rep = [](vector<int> &vec) {
					int i = 0, j = 1, k, l = (int)vec.size();
					vec.push_back(-1);
					while(i < l && j < l) {
						for(k = 0; k < l && vec[i + k] == vec[j + k]; ++k);
						if(k == l)
							break;
						if(vec[i + k] > vec[j + k]) {
							i = i + k + 1 > j ? i + k + 1 : j + 1;
						} else {
							j = j + k + 1 > i ? j + k + 1 : i + 1;
						}
					}
					if(i >= l)
						i = j;
					vec.pop_back();
					rotate(vec.begin(), vec.begin() + i, vec.end());
				};
				get_min_rep(col);
				vector<int> tmp(col.begin(), col.end());
				reverse(tmp.begin(), tmp.end());
				get_min_rep(tmp);
				int sgn = cmp(col, tmp);
				if(sgn > 0)
					col.swap(tmp);
				map<vector<int>, pair<int, int> >::iterator it = Hash2.find(col);
				if(it != Hash2.end()) {
					++(it -> second).second;
				} else {
					int len = (int)col.size(), per = len;
					for(int i = 2, tmp = len; i <= tmp; ++i) {
						if(i * i > tmp)
							i = tmp;
						if(tmp % i > 0)
							continue;
						for(tmp /= i; tmp % i == 0; tmp /= i);
						for( ; per % i == 0; per /= i) {
							bool chk = 1;
							for(int u = 0, v = per / i; chk && v < len; )
								chk &= col[u++] == col[v++];
							if(!chk)
								break;
						}
					}
					Hash2.insert(make_pair(col, make_pair((len / per) << !sgn, 1)));
				}
				continue;
			}
			if(deg[i] == 2) {
				reverse(col.begin(), col.end());
				vis[i] = 0;
				las = e[i][0].first;
				if(!vis[las])
					las = e[i][1].first;
				for(u = i; !vis[u]; ) {
					vis[u] = 1;
					int v = -1;
					for(int i = 0; i < deg[u]; ++i) {
						int w = e[u][i].first;
						if(w != las) {
							col.push_back(e[u][i].second);
							v = w;
							break;
						}
					}
					if(v == -1)
						break;
					las = u;
					u = v;
				}
			}
			vector<int> tmp(col.begin(), col.end());
			reverse(tmp.begin(), tmp.end());
			int sgn = cmp(col, tmp);
			if(sgn > 0)
				col.swap(tmp);
			map<vector<int>, pair<int, int> >::iterator it = Hash1.find(col);
			if(it != Hash1.end()) {
				++(it -> second).second;
			} else {
				Hash1.insert(make_pair(col, make_pair(!sgn ? 2 : 1, 1)));
			}
		}
		int ans = 1;
		for(int i = 2; i <= Hash0; ++i)
			ans = (LL)ans * i % mod;
		for(auto &it : Hash1) {
			int ways = it.second.first, cnt = it.second.second;
			for(int i = 1; i <= cnt; ++i)
				ans = (LL)ans * ways % mod * i % mod;
		}
		for(auto &it : Hash2) {
			int ways = it.second.first, cnt = it.second.second;
			for(int i = 1; i <= cnt; ++i)
				ans = (LL)ans * ways % mod * i % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
