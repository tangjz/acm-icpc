#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, seed = 233, mod = (int)1e9 + 7;
int t, n, rt, ch[2][maxn], sz[maxn], low[maxn], tot, idx[maxn];
void pfs(int u) {
	if(sz[u] != -1)
		return;
	sz[u] = 1;
	int v = ch[0][u];
	if(v) {
		pfs(v);
		sz[u] += sz[v];
		low[u] = min(low[u], low[v]);
	}
	v = ch[1][u];
	if(v) {
		pfs(v);
		sz[u] += sz[v];
		low[u] = min(low[u], low[v]);
	}
}
void dfs(int u) {
	int o = 0;
	if(low[u] == u) {
		if(sz[ch[0][u]] > sz[ch[1][u]] || (sz[ch[0][u]] == sz[ch[1][u]] && low[ch[0][u]] > low[ch[1][u]]))
			o ^= 1;
	} else if(!ch[0][u] || (ch[1][u] && low[ch[0][u]] > low[ch[1][u]]))
		o ^= 1;
	if(ch[o][u])
		dfs(ch[o][u]);
	idx[u] = ++tot;
	o ^= 1;
	if(ch[o][u])
		dfs(ch[o][u]);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d%d", ch[0] + i, ch[1] + i);
			sz[i] = -1;
			low[i] = i;
		}
		for(int i = 1; i <= n; ++i) {
			pfs(i);
			if(sz[i] == n)
				rt = i;
		}
		tot = 0;
		dfs(rt);
		int ans = 0;
		for(int i = n; i >= 0; --i)
			ans = ((LL)ans * seed + (idx[i] ^ i)) % mod;
		printf("%d\n", ans);
	}
}