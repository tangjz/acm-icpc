#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1;
int n, rt, sz[maxn];
vector<int> e[maxn];
void pfs(int u) {
	sz[u] = 1;
	for(int v : e[u]) {
		pfs(v);
		sz[u] += sz[v];
	}
}
void dfs(int u) {
	for(int v : e[u])
		if(!(sz[v] & 1))
			dfs(v);
	printf("%d\n", u);
	for(int v : e[u])
		if(sz[v] & 1)
			dfs(v);
}
int main() {
	scanf("%d", &n);
	if(!(n & 1)) {
		puts("NO");
		return 0;
	}
	for(int i = 1; i <= n; ++i) {
		int p;
		scanf("%d", &p);
		if(p) {
			e[p].push_back(i);
		} else {
			rt = i;
		}
	}
	pfs(rt);
	puts("YES");
	dfs(rt);
	return 0;
}