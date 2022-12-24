#include <bits/stdc++.h>
const int maxn = (int)7e5 + 1, mod = 998244353;
int n, m, a[maxn], ans = 1;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	std::sort(a, a + n);
	for(int i = 0, j = 0; i < n; ++i) {
		for( ; a[i] - a[j] > m; ++j);
		ans = ans * (i - j + 1LL) % mod;
	}
	printf("%d\n", ans);
	return 0;
}