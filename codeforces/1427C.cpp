#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)3e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

inline void upd_max(int &x, int y) {
	x < y && (x = y);
}
inline int dist(pair<int, int> lft, pair<int, int> rht) {
	return abs(lft.first - rht.first) + abs(lft.second - rht.second);
}

void solve() {
	int n, m;
	static pair<int, int> a[maxn];
	static int tim[maxn], dp[maxn];
	scanf("%d%d", &m, &n);
	int ans = 0, upp = (m - 1) * 2;
	tim[0] = 0;
	a[0] = {1, 1};
	for(int i = 1, j = 0, pre = -1; i <= n; ++i) {
		scanf("%d%d%d", tim + i, &a[i].first, &a[i].second);
		for( ; j < i && tim[i] - tim[j] >= upp; ++j)
			upd_max(pre, dp[j]);
		int &cur = dp[i] = pre;
		for(int k = j; k < i; ++k)
			if(tim[i] - tim[k] >= dist(a[i], a[k]))
				upd_max(cur, dp[k]);
		if(cur < 0) {
			--i;
			--n;
		} else {
			upd_max(ans, ++cur);
		}
	}
	printf("%d\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}