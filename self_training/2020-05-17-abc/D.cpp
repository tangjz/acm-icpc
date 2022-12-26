#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n, m;
		static vector<int> e[maxn];
		static int que[maxn], par[maxn];
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			vector<int>().swap(e[i]);
			par[i] = 0;
		}
		par[1] = 1;
		for(int i = 1; i <= m; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		int tot = 1;
		que[1] = 1;
		for(int i = 1; i <= tot; ++i) {
			int u = que[i];
			for(int v : e[u])
				if(!par[v]) {
					par[v] = u;
					que[++tot] = v;
				}
		}
		if(tot < n) {
			puts("No");
		} else {
			puts("Yes");
			for(int i = 2; i <= n; ++i)
				printf("%d\n", par[i]);
		}
	}
	return 0;
}