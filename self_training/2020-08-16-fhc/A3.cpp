#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, maxv = (int)5e8 + 1, mod = (int)1e9 + 7;
int n, p[maxn], w[maxn], h[maxn];
int solve() {
	static int ctr; ctr = 0;
	int ans = 1, tot = 0;
	LL sum = 0;
	map<int, int> seg;
	seg[0] = seg[maxv << 1] = 0;
	auto makePoint = [&](int pos) { ++ctr;
		auto it = --seg.upper_bound(pos);
		if((it -> first) < pos)
			seg.insert({pos, it -> second});
	};
	for(int i = 1; i <= n; ++i) {
		makePoint(p[i]);
		makePoint(p[i] + w[i]);
		int pre = (--seg.lower_bound(p[i])) -> second;
		for(auto it = seg.lower_bound(p[i]); it != seg.end() && (it -> first) <= p[i] + w[i]; ) { ++ctr;
			auto jt = it++;
			if((jt -> first) < p[i] + w[i] && (jt -> second) < h[i]) {
				if(!(jt -> second))
					sum += ((it -> first) - (jt -> first)) * 2;
				sum -= abs(pre - (jt -> second)) + abs((jt -> second) - (it -> second));
				jt -> second = h[i];
				sum += abs(pre - (jt -> second)) + abs((jt -> second) - (it -> second));
			}
			if(pre == (jt -> second)) {
				int pos = jt -> first;
				it = seg.erase(jt);
			} else {
				pre = jt -> second;
			}
		}
		ans = ans * (sum % mod) % mod;
		// printf("#%d: %lld\n", i, sum);
	}
	fprintf(stderr, "ctr: %d\t", ctr);
	return ans;
}
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int K, A, B, C, D;
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= K; ++i)
			scanf("%d", p + i);
		scanf("%d%d%d%d", &A, &B, &C, &D);
		for(int i = K + 1; i <= n; ++i)
			p[i] = ((LL)A * p[i - 2] + (LL)B * p[i - 1] + C) % D + 1;
		for(int i = 1; i <= K; ++i)
			scanf("%d", w + i);
		scanf("%d%d%d%d", &A, &B, &C, &D);
		for(int i = K + 1; i <= n; ++i)
			w[i] = ((LL)A * w[i - 2] + (LL)B * w[i - 1] + C) % D + 1;
		for(int i = 1; i <= K; ++i) {
			scanf("%d", h + i);
			assert(i == 1 || h[i] >= h[i - 1]);
		}
		scanf("%d%d%d%d", &A, &B, &C, &D);
		for(int i = K + 1; i <= n; ++i) {
			h[i] = ((LL)A * h[i - 2] + (LL)B * h[i - 1] + C) % D + 1;
			assert(h[i] >= h[i - 1]);
		}
		printf("Case #%d: %d\n", Case, solve());
	}
	return 0;
}
