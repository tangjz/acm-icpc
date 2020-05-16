#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, deg[maxn], lev[maxn], ctr[maxn], tot, que[maxn];
vector<int> e[maxn];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		++deg[u];
		++deg[v];
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i = 1; i <= n; ++i)
		if(deg[i] == 1) {
			lev[i] = 0;
			que[tot++] = i;
		} else {
			lev[i] = -1;
		}
	for(int i = 0; i < tot; ++i) {
		int u = que[i];
		if(lev[u] && ctr[u] < 3) {
			puts("No");
			return 0;
		}
		for(int v : e[u]) {
			if(lev[v] == -1) {
				que[tot++] = v;
				lev[v] = lev[u] + 1;
			} else if(abs(lev[u] - lev[v]) != 1) {
				puts("No");
				return 0;
			}
			ctr[v] += lev[u] < lev[v];
		}
	}
	if(tot != n || lev[que[tot - 1]] != m || (n > 1 && lev[que[tot - 2]] == lev[que[tot - 1]])) {
		puts("No");
	} else {
		puts("Yes");
	}
	return 0;
}