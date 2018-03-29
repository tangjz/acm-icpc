#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 61;
int n, m, mod, inv[maxn], gcd[maxn][maxn], pw[maxn * maxn], path[maxn], ans;
void dfs(int cnt, int sum, int low, int ways, int blocks) {
	if(sum == n) {
		ans = (ans + (LL)ways * pw[blocks]) % mod;
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
		dfs(cnt + 1, sum + i, i, (LL)ways * inv[i] % mod * inv[times] % mod, blocks + delta);
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &mod);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	for(int i = 1; i <= n; ++i)
		gcd[0][i] = gcd[i][0] = i;
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
			gcd[i][j] = gcd[j][i] = gcd[i][j - i];
	pw[0] = 1;
	for(int i = 1; i <= n * (n - 1) / 2; ++i)
		pw[i] = (LL)pw[i - 1] * m % mod;
	dfs(0, 0, 1, 1, 0);
	printf("%d\n", ans);
	return 0;
}
