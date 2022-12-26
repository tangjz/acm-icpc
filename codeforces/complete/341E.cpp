#include <bits/stdc++.h>
using namespace std;

typedef signed i32;
typedef unsigned u32;
typedef long long i64;
typedef unsigned long long u64;
// typedef __int128_t i128;
// typedef __uint128_t u128;
typedef float f32;
typedef double f64;
typedef long double f128;

const int maxn = (int)1e6 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n;
	vector<pair<int, int> > vec, sol;
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		if(x > 0)
			vec.push_back({x, i});
	}
	if(vec.size() < 2) {
		puts("-1");
		return;
	}
	while(vec.size() > 2) {
		pair<int, int> seq[3];
		for(int i = 0; i < 3; ++i) {
			seq[i] = vec.back();
			vec.pop_back();
		}
		sort(seq, seq + 3);
		while(seq[0].first > 0) {
			if(seq[1].first == seq[2].first) {
				sol.push_back({seq[2].second, seq[1].second});
				seq[2].first <<= 1;
				seq[1].first = 0;
				swap(seq[0], seq[1]);
				continue;
			}
			int msk = seq[1].first / seq[0].first;
			while(msk > 0) {
				int i = 2 - (msk & 1);
				sol.push_back({seq[0].second, seq[i].second});
				seq[i].first -= seq[0].first;
				seq[0].first <<= 1;
				msk >>= 1;
			}
			sort(seq, seq + 3);
		}
		for(int i = 0; i < 3; ++i)
			if(seq[i].first > 0)
				vec.push_back(seq[i]);
	}
	printf("%d\n", (int)sol.size());
	for(auto &it: sol)
		printf("%d %d\n", it.first, it.second);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}
