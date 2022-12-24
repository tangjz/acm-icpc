#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int t, n, seq[2][maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		seq[0][0] = seq[1][0] = 0;
		while(n--) {
			int x;
			scanf("%d", &x);
			seq[x & 1][++seq[x & 1][0]] = x;
		}
		LL ans = 0;
		for(int i = 0; i < 2; ++i) {
			ans += seq[i][0] * (seq[i][0] - 1LL) / 2;
			sort(seq[i] + 1, seq[i] + seq[i][0] + 1);
			for(int j = 1, k = 1; j <= seq[i][0]; j = k) {
				for( ; k <= seq[i][0] && (seq[i][j] >> 2) == (seq[i][k] >> 2); ++k);
				ans -= (k - j) * (k - j - 1LL) / 2;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
