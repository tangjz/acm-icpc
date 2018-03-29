#include <bits/stdc++.h>
using namespace std;
const int maxn = 501, mod = (int)1e9 + 7;
int n, f[2][maxn][maxn], cur, pre = 1;
char buf[maxn][maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%s", buf[i]);
	if(buf[0][0] != buf[n - 1][n - 1]) {
		puts("0");
		return 0;
	}
	f[cur][0][n - 1] = 1;
	for(int i = 1; i <= n; ++i) {
		pre ^= 1;
		cur ^= 1;
		for(int j = 0; j < n; ++j)
			for(int k = j; k < n; ++k) {
				f[cur][j][k] = 0;
				if(i - 1 - j < 0 || n + n - 1 - i - k >= n || buf[j][i - 1 - j] != buf[k][n + n - 1 - i - k])
					continue;
				(f[cur][j][k] += f[pre][j][k]) >= mod && (f[cur][j][k] -= mod);
				j && (f[cur][j][k] += f[pre][j - 1][k]) >= mod && (f[cur][j][k] -= mod);
				k + 1 < n && (f[cur][j][k] += f[pre][j][k + 1]) >= mod && (f[cur][j][k] -= mod);
				j && k + 1 < n && (f[cur][j][k] += f[pre][j - 1][k + 1]) >= mod && (f[cur][j][k] -= mod);
			}
	}
	int ans = 0;
	for(int i = 0; i < n; ++i)
		(ans += f[cur][i][i]) >= mod && (ans -= mod);
	printf("%d\n", ans);
	return 0;
}
