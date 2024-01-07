#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1, mod = (int)1e9 + 7;
int t, n;
pair<int, LL> dp[2];
inline void upd(pair<int, LL> &x, pair<int, LL> y) {
	if(x.first < y.first || (x.first == y.first && x.second < y.second))
		x = y;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		dp[0] = dp[1] = make_pair(0, 0);
		for(int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			int o = x > 0;
			if(dp[!o].first > 0)
				upd(dp[o], make_pair(dp[!o].first + 1, dp[!o].second + x));
			upd(dp[o], make_pair(1, (LL)x));
		}
		upd(dp[0], dp[1]);
		printf("%lld\n", dp[0].second);
	}
	return 0;
}