#include <bits/stdc++.h>
const int maxn = (int)1e6 + 1, maxc = 19;
int n, m, c[maxc][maxn];
char buf[maxn];
int main() {
	scanf("%d%s", &n, buf);
	for(m = 0; (2 << m) <= n; ++m);
	for(int i = 0; i + 1 < n; ++i) {
		bool eq = buf[i] == buf[i + 1];
		for(int j = 1; j < m; ++j)
			c[j][i] = eq + (i < (1 << j) ? 0 : c[j][i - (1 << j)]);
	}
	scanf("%d", &n);
	while(n--) {
		int L, R;
		scanf("%d%d", &L, &R);
		int ans = 0, len = R - L + 1;
		for(m = 0; (1 << m) < len; ++m);
		assert(len == (1 << m));
		for(int i = 1; i < m; ++i) {
			int u = L - 1 - (1 << (i - 1)), sz = (R - u) >> i;
			int v = u + (sz << i), ctr = c[i][v] - (u < 0 ? 0 : c[i][u]);
			ans += std::min(ctr, sz - ctr);
		}
		printf("%d\n", (ans + 1) >> 1);
	}
	return 0;
}
