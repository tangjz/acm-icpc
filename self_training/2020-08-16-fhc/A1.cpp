#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;
int n, p[maxn], w, h[maxn];
int solve() {
	int ans = 1, tot = 0;
	LL sum = 0;
	static pair<int, int> seq[maxn << 1 | 1];
	seq[tot++] = {0, 0};
	for(int i = 1, j, k; i <= n; ++i) {
		for(j = tot - 1; j >= 0 && seq[j].first > p[i]; --j);
		if(seq[j].first < p[i]) {
			for(int k = tot - 1; k > j; --k)
				seq[k + 1] = seq[k];
			seq[j + 1] = {p[i], seq[j].second};
			++tot;
			++j;
		}
		assert(j > 0);
		seq[tot++] = {p[i] + w, 0};
		for(k = j; j < tot; ++j) {
			if(seq[j].first < p[i] + w && seq[j].second < h[i]) {
				assert(j + 1 < tot);
				if(!seq[j].second)
					sum += (seq[j + 1].first - seq[j].first) * 2;
				sum -= abs(seq[k - 1].second - seq[j].second) + abs(seq[j].second - seq[j + 1].second);
				seq[j].second = h[i];
				sum += abs(seq[k - 1].second - seq[j].second) + abs(seq[j].second - seq[j + 1].second);
			}
			if(seq[k - 1].second != seq[j].second)
				seq[k++] = seq[j];
		}
		tot = k;
		ans = ans * (sum % mod) % mod;
		// printf("#%d: %lld\n", i, sum);
	}
	return ans;
}
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int K, A, B, C, D;
		scanf("%d%d%d", &n, &K, &w);
		for(int i = 1; i <= K; ++i) {
			scanf("%d", p + i);
			assert(i == 1 || p[i] > p[i - 1]);
		}
		scanf("%d%d%d%d", &A, &B, &C, &D);
		for(int i = K + 1; i <= n; ++i) {
			p[i] = ((LL)A * p[i - 2] + (LL)B * p[i - 1] + C) % D + 1;
			assert(p[i] > p[i - 1]);
		}
		for(int i = 1; i <= K; ++i)
			scanf("%d", h + i);
		scanf("%d%d%d%d", &A, &B, &C, &D);
		for(int i = K + 1; i <= n; ++i)
			h[i] = ((LL)A * h[i - 2] + (LL)B * h[i - 1] + C) % D + 1;
		printf("Case #%d: %d\n", Case, solve());
	}
	return 0;
}
