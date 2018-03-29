#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 61, mod = 998244353;
int n, seq[maxn], inv[maxn], ans;
void dfs(int sum, int low, int ways) {
	if(sum == n) {
		ans = (ans + (LL)ways * ways % mod * low) % mod;
		return;
	}
	for(int i = low; sum + i <= n; ++i) {
		if(sum + i < n && sum + i + i > n)
			continue;
		int coeff = 1;
		for(int j = 1; j <= i; ++j)
			coeff = (LL)coeff * (sum + j) % mod * inv[++seq[j] + i - j] % mod;
		dfs(sum + i, i, (LL)ways * coeff % mod);
		for(int j = 1; j <= i; ++j)
			--seq[j];
	}
}
int main() {
	scanf("%d", &n);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	dfs(0, 1, 1);
	for(int i = 2; i <= n; ++i)
		ans = (LL)ans * inv[i] % mod;
	printf("%d\n", ans);
	return 0;
}
