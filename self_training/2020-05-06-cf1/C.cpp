#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
#define x first
#define y second
const int maxn = (int)3e5 + 1, maxd = 26, mod = (int)1e9 + 7;

int main() {
	int t = 1;
	// scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int n, m;
		scanf("%d%d", &n, &m);
		vector<int> deg(n, 0), dsu(n, -1);
		vector<vector<int> > e(n, vector<int>()), re(n, vector<int>());
		for(int i = 0; i < m; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[--u].push_back(--v);
			re[v].push_back(u);
			++deg[v];
		}
		queue<int> Q;
		for(int i = 0; i < n; ++i)
			if(!deg[i])
				Q.push(i);
		int cnt = 0;
		while(!Q.empty()) {
			int u = Q.front();
			++cnt;
			Q.pop();
			for(int &v : e[u])
				if(!(--deg[v]))
					Q.push(v);
		}
		if(cnt < n) {
			puts("-1");
			continue;
		}
		vector<char> vis(n, 0), rvis(n, 0);
		function<void(int)> dfs = [&](int u) {
			if(vis[u])
				return;
			vis[u] = 1;
			for(int &v : e[u])
				dfs(v);
		};
		function<void(int)> rdfs = [&](int u) {
			if(rvis[u])
				return;
			rvis[u] = 1;
			for(int &v : re[u])
				rdfs(v);
		};
		int ans = 0;
		static char buf[maxn];
		for(int i = 0; i < n; ++i) {
			buf[i] = "AE"[vis[i] || rvis[i]];
			ans += buf[i] == 'A';
			dfs(i);
			rdfs(i);
		}
		buf[n] = '\0';
		printf("%d\n%s\n", ans, buf);
	}
	return 0;
}