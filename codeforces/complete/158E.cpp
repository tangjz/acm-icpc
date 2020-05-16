#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)4e3 + 3, maxv = 86400;
int n, m, sta[maxn], len[maxn], f[maxn][maxn], ans;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= m; ++i)
		f[0][i] = 1;
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", sta + i, len + i);
		for(int j = 0; j <= m; ++j) {
			f[i][j] = max(f[i - 1][j], sta[i]) + len[i];
			if(j)
				f[i][j] = min(f[i][j], f[i - 1][j - 1]);
		}
	}
	sta[n + 1] = maxv + 1;
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= m; ++j)
			ans = max(ans, sta[min(i + m - j, n) + 1] - f[i][j]);
	printf("%d\n", ans);
	return 0;
}