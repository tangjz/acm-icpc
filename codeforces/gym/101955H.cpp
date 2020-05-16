#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 71, maxm = 2417;
int t, n, mod, f[maxm], inv[maxm], Gcd[maxn][maxn], path[maxn];
void dfs(int cnt, int sum, int low, int ways, int blocks, bool odd) {
	if(sum == n) {
		blocks -= cnt - odd;
		(f[blocks] += ways) >= mod && (f[blocks] -= mod);
		return;
	}
	for(int i = low; sum + i <= n; ++i) {
		if(sum + i < n && sum + i + i > n)
			continue;
		int delta = i >> 1, times = 1;
		for(int j = 0; j < cnt; ++j) {
			delta += Gcd[i][path[j]];
			times += path[j] == i;
		}
		path[cnt] = i;
		dfs(cnt + 1, sum + i, i, (LL)ways * inv[i * times] % mod, blocks + delta, odd || (i & 1));
	}
}
int main() {
	for(int i = 1; i < maxn; ++i)
		Gcd[0][i] = Gcd[i][0] = i;
	for(int i = 1; i < maxn; ++i)
		for(int j = i; j < maxn; ++j)
			Gcd[i][j] = Gcd[j][i] = Gcd[i][j - i];
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &mod);
		inv[1] = 1;
		for(int i = 2; i <= n; ++i)
			inv[i] = mod - (mod / i * (LL)inv[mod % i] % mod);
		int edges = n * (n - 1) / 2;
		memset(f, 0, (edges + 1) * sizeof(int));
		dfs(0, 0, 1, 1, 0, 0);
		for(int i = edges - 1; i >= 0; --i) {
			(f[i] += f[i + 1]) >= mod && (f[i] -= mod);
			(f[i] += f[i + 1]) >= mod && (f[i] -= mod);
		}
		printf("Case #%d: %d\n", Case, f[0]);
	}
	return 0;
}
