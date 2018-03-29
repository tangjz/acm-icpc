#include <bits/stdc++.h>
using namespace std;
const int maxn = 61, mod = 997;
int n, inv[maxn], gcd[maxn][maxn], pw[maxn * maxn], path[maxn], ans;
void dfs(int cnt, int sum, int low, int ways, int blocks) {
	if(sum == n) {
		ans = (ans + ways * pw[blocks]) % mod;
		return;
	}
	for(int i = low; sum + i <= n; ++i) {
		if(sum + i < n && sum + i + i > n)
			continue;
		int delta = i >> 1, times = 1;
		for(int j = 0; j < cnt; ++j) {
			delta += gcd[i][path[j]];
			times += path[j] == i;
		}
		path[cnt] = i;
		dfs(cnt + 1, sum + i, i, ways * inv[i] * inv[times] % mod, blocks + delta);
	}
}
int main() {
	scanf("%d", &n);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - mod / i * inv[mod % i] % mod;
	for(int i = 1; i <= n; ++i)
		gcd[0][i] = gcd[i][0] = i;
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
			gcd[i][j] = gcd[j][i] = gcd[i][j - i];
	pw[0] = 1;
	for(int i = 1; i <= n * (n - 1) / 2; ++i)
		pw[i] = 2LL * pw[i - 1] % mod;
	dfs(0, 0, 1, 1, 0);
	printf("%d\n", ans);
	return 0;
}
