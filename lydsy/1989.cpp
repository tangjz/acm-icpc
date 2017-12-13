#include <cstdio>
#include <cstring>
const int maxn = 20001;
int n, lnk[maxn], nxt[maxn], vtx[maxn];
double ans;
int dfs(int u, int fa) {
	int su = 1;
	for(int it = lnk[u]; it; it = nxt[it]) {
		if(vtx[it] == fa)
			continue;
		int sv = dfs(vtx[it], u);
		su += sv;
		ans += sv * sv * (double)(n - sv) * (n - sv);
	}
	return su;
}
int main() {
	while(scanf("%d", &n) == 1) {
		memset(lnk + 1, 0, n * sizeof(int));
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			nxt[i << 1] = lnk[u];
			vtx[i << 1] = v;
			lnk[u] = i << 1;
			nxt[i << 1 | 1] = lnk[v];
			vtx[i << 1 | 1] = u;
			lnk[v] = i << 1 | 1;
		}
		ans = 0;
		dfs(1, -1);
		printf("%.6f\n", ans * 4 / (n * n * (n - 1.0) * (n - 1)));
	}
	return 0;
}
