#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, INF = ~0u >> 1;
int t, n, a[maxn], cur, pre = 1;
LL f[2][2], g[2][2];
vector<int> e[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 2, p; i <= n; ++i) {
			scanf("%d", &p);
			e[p].push_back(i);
		}
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		f[cur][0] = max(a[1], 0);
		f[cur][1] = 0;
		g[cur][0] = min(a[1], 0);
		g[cur][1] = 0;
		for(int i = 1; i <= n; ++i) {
			int sz = e[i].size();
			if(!sz)
				continue;
			swap(cur, pre);
			sort(e[i].begin(), e[i].end(), [&](int const &u, int const &v) {
				return a[u] < a[v];
			});
			f[cur][0] = f[pre][0] + max(a[e[i][sz - 1]], 0);
			f[cur][1] = f[pre][1] + max(a[e[i][sz - 1]], 0);
			g[cur][0] = g[pre][0] + min(a[e[i][0]], 0);
			g[cur][1] = g[pre][1] + min(a[e[i][0]], 0);
			if(sz > 1) {
				f[cur][1] = max(f[cur][1], f[cur][0] + max(a[e[i][sz - 2]], 0));
				g[cur][1] = min(g[cur][1], g[cur][0] + min(a[e[i][1]], 0));
			}
			vector<int>().swap(e[i]);
		}
		printf("%I64d %I64d\n", max(f[cur][0], f[cur][1]), min(g[cur][0], g[cur][1]));
	}
}
