#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, maxc = 26;
int t, n, m, dep[maxn], e[maxn][maxc | 1], ord[maxn], f[maxn], dp[maxn][2];
char buf[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &m);
		n = 0;
		memset(e[0], 0, sizeof e[0]);
		while(m--) {
			scanf("%s", buf);
			for(int i = 0, rt = 0; buf[i]; ++i) {
				int o = buf[i] - 'a';
				if(!e[rt][o]) {
					e[rt][o] = ++n;
					memset(e[n], 0, sizeof e[0]);
					dep[n] = dep[rt] + 1;
				}
				rt = e[rt][o];
			}
		}
		n = 0;
		for(int i = 0; i < maxc; ++i)
			if(e[0][i]) {
				f[e[0][i]] = 0;
				ord[++n] = e[0][i];
			}
		for(int i = 1; i <= n; ++i) {
			int u = ord[i];
			for(int j = 0; j < maxc; ++j)
				if(e[u][j]) {
					int v = e[u][j], w = f[u];
					for( ; w && !e[w][j]; w = f[w]);
					f[v] = e[w][j];
					ord[++n] = v;
				}
		}
		memset(dp, 0, (n + 1) * sizeof(dp[0]));
		for(int i = n; i >= 1; --i) {
			int u = ord[i], p = f[u], w = max(dp[u][0], ++dp[u][1]);
			dp[p][0] += w;
			dp[p][1] += dep[p] + 1 < dep[u] ? w : dp[u][0];
		}
		printf("%d\n", dp[0][0]);
	}
	return 0;
}