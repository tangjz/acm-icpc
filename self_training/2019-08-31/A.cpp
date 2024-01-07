#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int t, n, a[2][maxn];
LL f[2][maxn];
vector<int> e[maxn];
void dfs(int u, int fa) {
	f[0][u] = f[1][u] = 0;
	for(int v : e[u]) {
		if(v == fa)
			continue;
		dfs(v, u);
		f[0][u] += max(f[0][v] + abs(a[0][u] - a[0][v]), f[1][v] + abs(a[0][u] - a[1][v]));
		f[1][u] += max(f[0][v] + abs(a[1][u] - a[0][v]), f[1][v] + abs(a[1][u] - a[1][v]));
	}
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", a[0] + i, a[1] + i);
		dfs(1, -1);
		printf("%lld\n", max(f[0][1], f[1][1]));
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
	}
	return 0;
}