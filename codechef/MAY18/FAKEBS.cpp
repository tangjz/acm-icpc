#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 17;
int t, n, m, a[maxn], que[maxn], path[maxd], dir[maxd], ans[maxn];
void dfs(int dep, int L, int R) {
	if(L > R)
		return;
	int M = (L + R) >> 1, idx = lower_bound(que + 1, que + n + 1, a[M]) - que;
	int c0 = 0, c1 = 0, d0 = 0, d1 = 0;
	for(int i = 0; i < dep; ++i)
		if(!dir[i]) {
			c0 += a[path[i]] < a[M];
			++d1;
		} else {
			c1 += a[path[i]] > a[M];
			++d0;
		}
	ans[idx] = min(c0, c1);
	if(ans[idx] < c0) {
		if(n - idx < d1)
			ans[idx] = -1;
		else
			ans[idx] = c0;
	} else if(ans[idx] < c1) {
		if(idx - 1 < d0)
			ans[idx] = -1;
		else
			ans[idx] = c1;
	}
	path[dep] = M;
	dir[dep] = 0;
	dfs(dep + 1, L, M - 1);
	dir[dep] = 1;
	dfs(dep + 1, M + 1, R);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			que[i] = a[i];
		}
		sort(que + 1, que + n + 1);
		dfs(0, 1, n);
		while(m--) {
			int x;
			scanf("%d", &x);
			printf("%d\n", ans[lower_bound(que + 1, que + n + 1, x) - que]);
		}
	}
	return 0;
}
