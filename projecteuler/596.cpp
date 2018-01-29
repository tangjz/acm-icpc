#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e9 + 7;
int sum(LL L, LL R) {
	LL x = L + R, y = R - L + 1;
	return x & 1 ? x % mod * (y / 2 % mod) % mod : x / 2 % mod * (y % mod) % mod;
}
int solve(LL n) {
	int ret = 0;
	for(LL i = 1, j, k; i <= n; i = j + 1) {
		k = n / i;
		j = n / k;
		ret = (ret + k % mod * sum(i, j)) % mod;
	}
	return ret;
}
int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		int ans = (8LL * solve((LL)n * n) - 32LL * solve((LL)n * n / 4) + 1) % mod;
		printf("%d\n", ans < 0 ? ans + mod : ans);
	}
	return 0;
}
