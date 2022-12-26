#include <bits/stdc++.h>
const int maxn = (int)5e3 + 1, mod = (int)1e6;
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	double dp[maxn] = {};
	for(int i = 1; i <= n; ++i) {
		dp[0] += 1;
		for(int j = 1; j <= m; ++j)
			dp[j] = std::max(0., ((dp[j] + 1) * i + (dp[j - 1] - 1) * j) / (i + j));
	}
	long long ans = floor(dp[m] * mod);
	printf("%d.%06d\n", (int)(ans / mod), (int)(ans % mod));
	return 0;
}
