#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
int t, n, m, rk, ctr[maxn], lim[maxn], adt[maxn];
long long ans;
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d%d", &n, &m, &rk);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", ctr + i);
			lim[i] = min(i, rk);
			adt[i] = 0;
		}
		lim[rk] = 1;
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			if(u < v)
				swap(u, v);
			lim[u] = min(lim[u], v);
		}
		for(int i = 1; i <= n; ++i)
			++adt[lim[i]];
		ans = 0;
		for(int i = n, j = 0; i >= 1; --i) {
			int k = min(ctr[i], j += adt[i]);
			ans += (ctr[i] -= k);
			j -= k;
		}
		printf("Case #%d: %I64d\n", Case, ans);
	}
	return 0;
}
