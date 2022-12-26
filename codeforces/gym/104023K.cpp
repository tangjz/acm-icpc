#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e5 + 1, maxv = (int)1e9;

void solve() {
	int n;
	static int sum_n = 0;
	assert(
		scanf("%d", &n) == 1
		&& 1 <= n && n <= 100000
		&& (sum_n += n) <= 100000
	);
	pair<int, int> low = {INT_MAX, 0};
	vector<pair<int, int> > upp;
	upp.push_back({0, 0});
	for(int i = 0; i < n; ++i) {
		int t, k, x;
		assert(
			scanf("%d%d%d", &t, &k, &x) == 3
			&& 1 <= t && t <= 2
			&& 1 <= k && k <= maxv
			&& 1 <= x && x <= maxv
		);
		// L <= (2x/k-k+1)/2, R >= (2x/k+k-1)/2
		int L = ((x + x) / k - k + 1) / 2;
		int R = ((x + x - 1) / k + k + 1) / 2;
		if(t == 1) {
			low = {min(low.first, L), max(low.second, R)};
			continue;
		}
		upp.push_back({L, R});
	}
	sort(upp.begin(), upp.end());
	int sz = 0;
	for(auto &it: upp) {
		for( ; sz && it.second <= upp[sz - 1].second; --sz);
		upp[sz++] = it;
	}
	upp.resize(sz);
	if(!sz || upp[sz - 1].first < low.first) {
		puts("-1");
		return;
	}
	assert(low.first <= low.second);
	LL ans = 0;
	for(int i = 1; i < sz; ++i) {
		int xL = max(upp[i - 1].first, 0) + 1;
		int xR = min(upp[i].first, low.first);
		int yL = low.second;
		int yR = upp[i].second - 1;
		if(xL <= xR && yL <= yR) {
			ans += (xR - xL + 1LL) * (yR - yL + 1);
		}
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
