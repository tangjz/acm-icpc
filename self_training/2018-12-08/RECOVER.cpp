#include <bits/stdc++.h>
using namespace std;
const int maxn = 201, maxs = 40001, maxd = 13;
vector<pair<int, int> > dt;
int t, n, m, s, mat[maxn][maxn];
set<int> e[maxs];
bool solve() {
	static int ctr[maxd], deg[maxn][maxn];
	static bool vis[maxs];
	memset(ctr, 0, sizeof ctr);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			deg[i][j] = 0;
			for(auto &it : dt) {
				int x = i + it.first, y = j + it.second;
				if(x < 1 || x > n || y < 1 || y > n)
					continue;
				++deg[i][j];
			}
			++ctr[deg[i][j]];
		}
	for(int i = 1; i <= s; ++i) {
		if(e[i].size() >= maxd)
			return 0;
		--ctr[e[i].size()];
		vis[i] = 0;
	}
	for(int i = 1; i < maxd; ++i)
		if(ctr[i])
			return 0;
	if(n <= 2) {
		for(int i = 1, k = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j, ++k)
				mat[i][j] = k;
	} else {
		auto calc = [&](int x1, int y1, int x2, int y2) {
			int ret = 0;
			for(auto &it : dt) {
				int x3 = x2 + it.first, y3 = y2 + it.second;
				if(x3 < 1 || x3 > n || y3 < 1 || y3 > n)
					continue;
				int dis = abs(x1 - x3) + abs(y1 - y3);
				ret += dis == 1 || dis == 2;
			}
			return ret;
		};
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) {
				int p, q, r;
				if(j == 1) {
					p = i > 1 ? mat[i - 1][j + 1] : -1;
					q = i > 1 ? mat[i - 1][j] : -1;
					r = i > 1 ? calc(i, j, i - 1, j) : -1;
				} else if(j == 2) {
					p = i > 1 ? mat[i - 1][j] : -1;
					q = mat[max(i - 1,  1)][j - 1];
					r = calc(i, j, max(i - 1, 1), j - 1);
				} else {
					p = mat[i][j - 1];
					q = mat[i][j - 2];
					r = calc(i, j, i, j - 2);
				}
				mat[i][j] = -1;
				if(p == -1) {
					for(int u = 1; u <= s; ++u)
						if(!vis[u] && e[u].size() == deg[i][j]) {
							if(r != -1) {
								int ret = 0;
								for(auto &v : e[u])
									ret += e[q].count(v);
								if(ret != r)
									continue;
							}
							mat[i][j] = u;
							vis[u] = 1;
							break;
						}
				} else {
					for(auto &u : e[q]) {
						if(!vis[u] && e[u].size() == deg[i][j] && e[p].count(u)) {
							int ret = 0;
							for(auto &v : e[u])
								ret += e[q].count(v);
							if(ret != r)
								continue;
							mat[i][j] = u;
							vis[u] = 1;
							break;
						}
					}
				}
				if(mat[i][j] == -1)
					return 0;
			}
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			int u = mat[i][j];
			for(auto &it : dt) {
				int x = i + it.first, y = j + it.second;
				if(x < 1 || x > n || y < 1 || y > n)
					continue;
				int v = mat[x][y];
				if(!e[u].count(v))
					return 0;
				e[u].erase(v);
			}
		}
	return 1;
}
int main() {
	for(int x = -2; x <= 2; ++x)
		for(int y = -2; y <= 2; ++y) {
			int dis = abs(x) + abs(y);
			if(dis == 1 || dis == 2)
				dt.push_back(make_pair(x, y));
		}
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		s = n * n;
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].insert(v);
			e[v].insert(u);
		}
		if(solve()) {
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
					printf("%d%c", mat[i][j], " \n"[j == n]);
		} else {
			puts("-1");
		}
		for(int i = 1; i <= s; ++i)
			set<int>().swap(e[i]);
	}
	return 0;
}
