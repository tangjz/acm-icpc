#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1, maxd = 1 << 9 | 1;
int n, m, mx, low, a[maxn], ans[maxn];
vector<int> e[maxd], sub[maxd];
struct Query {
	int k, x;
} b[maxn];
void dfs(int dep, int msk) {
	if(dep == mx) {
		for(int idx : e[msk]) {
			int val = 0, pos = b[idx].x;
			for(int dt : sub[b[idx].k])
				if(pos + dt <= n)
					val ^= a[pos + dt];
			ans[idx] = val;
		}
		return;
	}
	dfs(dep + 1, msk);
	for(int dt = 1 << dep, i = 1; i + dt <= n; ++i)
		a[i] ^= a[i + dt];
	dfs(dep + 1, msk | 1 << (dep - low));
	for(int dt = 1 << dep, i = n - dt; i >= 1; --i)
		a[i] ^= a[i + dt];
}
int main() {
	scanf("%d%d", &n, &m);
	for(mx = 0; 1 << mx <= n; ++mx);
	low = (mx + 1) >> 1;
	for(int i = 0; i < 1 << low; ++i)
		for(int j = 0; j <= i; ++j)
			if((i & j) == j)
				sub[i].push_back(j);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &b[i].k, &b[i].x);
		b[i].k &= (1 << mx) - 1;
		e[b[i].k >> low].push_back(i);
		b[i].k &= (1 << low) - 1;
	}
	dfs(low, 0);
	for(int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
