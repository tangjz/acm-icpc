#include <bits/stdc++.h>
using namespace std;
const int maxn = 51, maxm = 1501;

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int N, K, P;
		scanf("%d%d%d", &N, &K, &P);
		static int a[maxn], dp[maxm];
		memset(dp, 0, (P + 1) * sizeof(int));
		for(int i = 0; i < N; ++i) {
			a[0] = 0;
			for(int j = 1; j <= K; ++j) {
				scanf("%d", a + j);
				a[j] += a[j - 1];
			}
			for(int j = P; j >= 1; --j)
				for(int k = min(j, K); k >= 1; --k)
					dp[j] = max(dp[j], dp[j - k] + a[k]);
		}
		printf("Case #%d: %d\n", Case, dp[P]);
	}
	return 0;
}