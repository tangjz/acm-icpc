#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1, mod = (int)1e9 + 7;
int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		scanf("%d", &n);
		static int pw[maxn];
		pw[0] = 1;
		for(int i = 1; i <= n; ++i)
			pw[i] = (pw[i - 1] << 1) % mod;
		int zero = 0;
		map<pair<LL, LL>, pair<int, int> > ctr;
		for(int i = 0; i < n; ++i) {
			LL x, y;
			scanf("%lld%lld", &x, &y);
			if(!x && !y) {
				++zero;
				continue;
			}
			LL com = __gcd(abs(x), abs(y));
			int pos = 0;
			pair<LL, LL> cur = make_pair(x / com, y / com), best = cur;
			for(int j = 1; j < 4; ++j) {
				cur = make_pair(-cur.second, cur.first);
				if(cur < best) {
					best = cur;
					pos = j;
				}
			}
			auto &cnt = ctr[best];
			if(pos & 1) {
				++cnt.first;
			} else {
				++cnt.second;
			}
		}
		int ans = 1;
		for(auto &it : ctr) {
			auto &jt = it.second;
			int u = jt.first, v = jt.second;
			ans = (LL)ans * (pw[u] + pw[v] - 1) % mod;
		}
		ans = (ans + mod - 1 + zero) % mod;
		printf("%d\n", ans);
	}
	return 0;
}