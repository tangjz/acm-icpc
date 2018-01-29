#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1001, mod = (int)1e9 + 7;
int m, n, f[maxn], g[maxn];
LL seq[maxn];
char buf[maxn];
int main() {
	f[0] = g[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		for(int j = i; j >= 1; --j)
			g[j] = g[j - 1];
		f[i] = g[0] = g[i];
		for(int j = 1; j <= i; ++j)
			(g[j] += g[j - 1]) >= mod && (g[j] -= mod);
	}
	scanf("%d%d", &m, &n);
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf);
		for(int j = 0; j < m; ++j)
			seq[j] |= (LL)(buf[j] == '1') << i;
	}
	std::sort(seq, seq + m);
	int ans = 1;
	for(int i = 0, j = 0; i < m; i = j) {
		for( ; j < m && seq[i] == seq[j]; ++j);
		ans = (LL)ans * f[j - i] % mod;
	}
	printf("%d\n", ans);
	return 0;
}
