#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, f[maxn], g[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", f + i);
	for(int i = n - 1; i >= 0; --i)
		g[i] = max(f[i], i + 1 < n ? g[i + 1] - 1 : 0);
	long long ans = 0;
	for(int i = 0; i < n; ++i) {
		g[i] = max(g[i], i ? g[i - 1] : 0);
		ans += g[i] - f[i];
	}
	printf("%lld\n", ans);
	return 0;
}
