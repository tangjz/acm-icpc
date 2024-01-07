#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, maxv = (int)5e8 + 1, mod = (int)1e9 + 7;
int n, p[maxn], w[maxn], h[maxn];
int solve() {
	int ans = 1, tot = 0;
	LL sum = 0;
	static int pos[maxn << 1 | 1], val[maxn << 1 | 1], dsu[maxn << 1 | 1];
	pos[tot++] = 0;
	for(int i = 1; i <= n; ++i) {
		pos[tot++] = p[i];
		pos[tot++] = p[i] + w[i];
	}
	sort(pos, pos + tot);
	tot = unique(pos, pos + tot) - pos;
	for(int i = 0; i < tot; ++i) {
		val[i] = 0;
		dsu[i] = i;
	}
	auto dsu_find = [&](int x) {
		int rt = x;
		for( ; dsu[rt] != rt; rt = dsu[rt]);
		for(int tp; dsu[x] != rt; tp = dsu[x], dsu[x] = rt, x = tp);
		return rt;
	};
	for(int i = 1; i <= n; ++i) {
		int L = lower_bound(pos, pos + tot, p[i]) - pos;
		int R = lower_bound(pos, pos + tot, p[i] + w[i]) - pos;
		assert(L > 0);
		for(int j = dsu_find(L); j < R; j = dsu_find(j)) {
			sum += (pos[j + 1] - pos[j]) * 2;
			sum -= abs(val[j - 1] - val[j]) + abs(val[j] - val[j + 1]);
			val[j] = h[i];
			sum += abs(val[j - 1] - val[j]) + abs(val[j] - val[j + 1]);
			dsu[j] = j + 1;
		}
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
			assert(i == 1 || h[i] <= h[i - 1]);
		}
		scanf("%d%d%d%d", &A, &B, &C, &D);
		for(int i = K + 1; i <= n; ++i) {
			h[i] = ((LL)A * h[i - 2] + (LL)B * h[i - 1] + C) % D + 1;
			assert(h[i] <= h[i - 1]);
		}
		printf("Case #%d: %d\n", Case, solve());
	}
	return 0;
}
