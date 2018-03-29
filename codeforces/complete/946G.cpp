#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1;
int n, a[maxn], f[maxn], mx, g[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		int j = upper_bound(g + 1, g + mx + 1, a[i] - i) - g;
		mx = max(mx, j);
		f[i] = j;
		g[j] = a[i] - i;
	}
	int ans = max(n - 1 - mx, 0);
	mx = 0;
	for(int i = n; i > 1; --i) {
		int j = upper_bound(g + 1, g + mx + 1, -a[i - 1] + i - 1) - g;
		ans = min(ans, n - 1 - (f[i - 1] + j - 1));
		j = upper_bound(g + 1, g + mx + 1, -a[i] + i - 1) - g;
		mx = max(mx, j);
		g[j] = -a[i] + i - 1;
	}
	printf("%d\n", ans);
	return 0;
}
