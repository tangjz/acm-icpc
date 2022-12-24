#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e6 + 1;

void solve() {
	int n, m, mod;
	scanf("%d%d%d", &n, &m, &mod);
	vector<int> a(n), col(n, -1), que;
	vector<vector<int> > e(n);
	que.reserve(n);
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		(a[i] = y - x) < 0 && (a[i] += mod);
	}
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[--u].push_back(--v);
		e[v].push_back(u);
	}
	int c[2] = {}, s[2] = {};
	col[0] = 0;
	que.push_back(0);
	for(int i = 0; i < n; ++i) {
		int u = que[i];
		++c[col[u]];
		(s[col[u]] += a[u]) >= mod && (s[col[u]] -= mod);
		for(int v: e[u])
			if(col[v] == -1) {
				col[v] = !col[u];
				que.push_back(v);
			} else if(col[u] == col[v]) {
				printf("%d\n", n);
				return;
			}
	}
	int ans = 0;
	for(int i = 0; i < 2; ++i)
		if(s[i] == s[!i] || (s[i] + 1) % mod == s[!i])
			ans += c[i];
	printf("%d\n", ans);
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