#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 51, maxm = 651;

void solve() {
	int n, p, q, m; // val, sp, tot, mod
	scanf("%d%d%d%d", &n, &q, &p, &m);
	int upp = (n + 1) / 2 * (n / 2 + 1);
	static int bin[maxm][maxm];
	for(int i = 0; i <= upp; ++i) {
		bin[i][0] = bin[i][i] = 1;
		for(int j = 1; j < i; ++j)
			(bin[i][j] = bin[i - 1][j - 1] + bin[i - 1][j]) >= m && (bin[i][j] -= m);
	}
	static int f[maxn][maxn][maxn]; // sp, val, tot
	for(int i = 0; i <= p; ++i)
		for(int j = 0; j <= n; ++j)
			memset(f[i][j], 0, (q + 1) * sizeof(int));
	f[0][0][0] = 1;
	for(int t = 0; t < p; ++t)
		for(int i = !!t; i < n; ++i)
			for(int u = t; u < q; ++u) {
				if(!f[t][i][u])
					continue;
				for(int j = i + 1; j <= n; ++j) {
					int x = i * (j - i), y = x + (j - i);
					for(int v = u + 1, dt = 1; v <= q && dt <= y; ++v, ++dt)
						(f[t + 1][j][v] = (f[t + 1][j][v] + (LL)(bin[y][dt] - (dt <= x ? bin[x][dt] : 0)) * f[t][i][u]) % m) < 0 && (f[t + 1][j][v] += m);
				}
			}
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		int x = i * (n - i);
		for(int u = q, dt = 0; u > 0 && dt <= x; --u, ++dt)
			ans = (ans + (LL)bin[x][dt] * f[p][i][u]) % m;
	}
	printf("%d\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
