#include <bits/stdc++.h>
using namespace std;
const int maxn = 201;
int n, e[maxn][maxn], ord[maxn], col[maxn];
char ban[maxn][maxn];
bool cmp(int const &u, int const &v) {
	return e[u][0] > e[v][0]; // deg[u] > deg[v];
}
bool dfs(int dep) {
	if(dep > n)
		return 1;
	int u = ord[dep];
	for(int i = 1, msk = 1; i <= 4; ++i, msk <<= 1) {
		if(ban[dep][u] & msk)
			continue;
		bool chk = 1;
		memcpy(ban[dep + 1] + 1, ban[dep] + 1, n * sizeof(char));
		for(int j = 1; chk && j <= e[u][0]; ++j)
			chk &= (ban[dep + 1][e[u][j]] |= msk) < 15;
		col[u] = i;
		if(chk && dfs(dep + 1))
			return 1;
	}
	return 0;
}
int main() {
	while(scanf("%d", &n) == 1) {
		memset(ban, 0, sizeof ban);
		for(int u, v; scanf("%d-%d", &u, &v) == 2; ban[u][v] = ban[v][u] = 1);
		for(int i = 1; i <= n; ++i) {
			e[i][0] = 0; // deg[i]
			for(int j = 1; j <= n; ++j)
				if(i != j && ban[i][j])
					e[i][++e[i][0]] = j;
			ord[i] = i;
		}
		sort(ord + 1, ord + n + 1, cmp);
		for(int i = 1; i <= n; ++i)
			ban[1][i] = 0;
		dfs(1);
		for(int i = 1; i <= n; ++i)
			printf("%d %d\n", i, col[i]);
	}
	return 0;
}
