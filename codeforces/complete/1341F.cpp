#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)1e5 + 1, maxm = (int)1e6 + 1, mod = (int)1e9 + 7;
int n, m, mx;
vector<int> e[maxn];
pair<int, int> seq[maxm];
void dfs(int u, int p, int sta) {
	int sz = (int)e[u].size() - (p > 0), tim = sta;
	seq[m++] = make_pair(u, sta);
	for(int v : e[u]) {
		if(v == p)
			continue;
		if(tim == mx) { // p > 0
			tim = mx - sz - 1;
			seq[m++] = make_pair(u, tim);
		}
		dfs(v, u, tim + 1);
		seq[m++] = make_pair(u, ++tim);
	}
	if(p > 0 && tim != sta - 1)
		seq[m++] = make_pair(u, sta - 1);
}
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		mx = 0;
		for(int i = 1; i <= n; ++i)
			mx = max(mx, (int)e[i].size());
		m = 0;
		dfs(1, 0, 0);
		printf("%d\n", m);
		for(int i = 0; i < m; ++i)
			printf("%d %d\n", seq[i].first, seq[i].second);
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
	}
	return 0;
}
