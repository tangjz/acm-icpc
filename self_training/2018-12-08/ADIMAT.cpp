#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 551, mod = (int)1e9 + 7;
int n, m, pw[maxn][maxn], inv[maxn], path[maxn], f[maxn], g[maxn], ans;
void dfs(int cnt, int sum, int low, int ways) {
	if(sum == n) {
		for(int i = 1; i <= m; ++i)
			f[i] = 1;
		for(int i = 0; i < cnt; ++i) {
			int *coeff = pw[path[i]];
			for(int j = 1; j <= m; ++j)
				f[j] = (LL)f[j] * coeff[j] % mod;
		}
		memcpy(g + 1, f + 1, m * sizeof(int));
		for(int i = 1; i <= m; ++i) {
			for(int j = 1; j <= i; ++j)
				g[i] = (g[i] + (LL)f[j] * g[i - j]) % mod;
			g[i] = (LL)g[i] * inv[i] % mod;
		}
		ans = (ans + (LL)ways * g[m]) % mod;
		return;
	}
	for(int i = low; sum + i <= n; ++i) {
		if(sum + i < n && sum + i + i > n)
			continue;
		path[cnt] = i;
		int ctr = 0;
		for(int j = cnt; j >= 0 && path[j] == i; --j, ctr += i);
		dfs(cnt + 1, sum + i, i, (LL)ways * inv[ctr] % mod);
	}
}
int main() {
	pw[0][0] = 1;
	for(int i = 1; i < maxn; ++i) {
		(pw[0][i] = pw[0][i - 1] << 1) >= mod && (pw[0][i] -= mod);
		pw[i][0] = pw[0][i];
	}
	for(int i = 1; i < maxn; ++i)
		for(int j = i; j < maxn; ++j)
			pw[i][j] = pw[j][i] = pw[i][j - i];
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	scanf("%d%d", &n, &m);
	if(n > m)
		swap(n, m);
	dfs(0, 0, 1, 1);
	printf("%d\n", ans);
	return 0;
}