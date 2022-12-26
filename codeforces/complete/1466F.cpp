#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)5e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n, m, cnt = 0;
	static vector<int> e[maxn];
	static int dsu[maxn], idx[maxn];
	static bool vis[maxn];
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; ++i) {
		vector<int>().swap(e[i]);
		dsu[i] = -1;
		vis[i] = 0;
	}
	function<int(int)> dsuFind = [&](int x) -> int {
		return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
	};
	auto dsuMerge = [&](int u, int v) -> bool {
		u = dsuFind(u);
		v = dsuFind(v);
		if(u == v || vis[u] && vis[v])
			return 0;
		if(dsu[u] < dsu[v])
			swap(u, v);
		dsu[v] -= dsu[u] == dsu[v];
		vis[v] |= vis[u];
		dsu[u] = v;
		vis[u] = 0;
		return 1;
	};

	for(int i = 1; i <= m; ++i) {
		int typ, u, v;
		scanf("%d%d", &typ, &u);
		if(typ == 1) {
			int p = dsuFind(u);
			if(!vis[p]) {
				idx[++cnt] = i;
				vis[p] = 1;
			}
		} else {
			scanf("%d", &v);
			if(dsuMerge(u, v)) {
				idx[++cnt] = i;
			}
		}
	}

	int ans = 1;
	for(int i = 1; i <= cnt; ++i)
		(ans <<= 1) >= mod && (ans -= mod);
	printf("%d %d\n", ans, cnt);
	for(int i = 1; i <= cnt; ++i)
		printf("%d%c", idx[i], " \n"[i == cnt]);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
