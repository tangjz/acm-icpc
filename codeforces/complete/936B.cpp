#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 3;
int n, s, tot, path[maxn];
vector<int> e[maxn];
bool chk, vis[maxn], used[maxn];
void dfs(int u) {
	vis[u] = used[u] = 1;
	path[tot++] = u;
	if(u & 1 && !e[u].size()) {
		puts("Win");
		for(int i = 0; i < tot; ++i)
			printf("%d%c", path[i] >> 1, " \n"[i == tot - 1]);
		exit(0);
	}
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(vis[v])
			chk = 1;
		if(!used[v])
			dfs(v);
	}
	vis[u] = 0;
	--tot;
}
int main() {
	scanf("%d%*d", &n);
	for(int i = 1; i <= n; ++i) {
		int sz;
		scanf("%d", &sz);
		e[i << 1].reserve(sz);
		e[i << 1 | 1].reserve(sz);
		while(sz--) {
			int j;
			scanf("%d", &j);
			e[i << 1].push_back(j << 1 | 1);
			e[i << 1 | 1].push_back(j << 1);
		}
	}
	scanf("%d", &s);
	dfs(s << 1);
	puts(chk ? "Draw" : "Lose");
	return 0;
}
