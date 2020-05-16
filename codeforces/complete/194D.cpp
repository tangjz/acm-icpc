#include <bits/stdc++.h>
using namespace std;
const int maxn = 31;
const long long INF = ~0ull >> 1;
int n, m, dt, a[maxn][maxn], b[maxn], w[maxn], p[maxn];
long long ans = -INF;
void dfs(int dep, bool ban) {
	int *pa = a[dep];
	if(!((m - dep) & 1)) {
		long long tmp = 0;
		for(int i = 1; i <= n; ++i)
			tmp += pa[i] * w[i];
		ans = max(ans, tmp);
	}
	if(dep == m)
		return;
	int *ca = a[dep + 1];
	for(int i = 1; i <= n; ++i)
		ca[i] = pa[p[i]] + dt;
	dfs(dep + 1, 0);
	if(!ban) {
		for(int i = 1; i <= n; ++i)
			ca[i] = pa[i] ^ b[i];
		dfs(dep + 1, 1);
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &dt);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a[0] + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", b + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", w + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", p + i);
	dfs(0, 0);
	printf("%lld\n", ans);
	return 0;
}