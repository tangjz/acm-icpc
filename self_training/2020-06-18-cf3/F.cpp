#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1;
const int mod = (int)1e9 + 7;

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		static int a[maxn], ord[maxn];
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			scanf("%d", a + i);
			ord[i] = i;
		}
		sort(ord, ord + n, [&](int const &u, int const &v) {
			return a[u] < a[v] || (a[u] == a[v] && u < v);
		});
		int tot = 0;
		static pair<int, int> seg[maxn];
		for(int i = 0; i < n; ++i)
			if(!i || a[ord[i - 1]] != a[ord[i]]) {
				seg[tot++] = {i, i};
			} else {
				seg[tot - 1].second = i;
			}
		static int addL[maxn], addR[maxn];
		for(int i = 0; i < tot; ++i) {
			int pL, pR, qL, qR;
			tie(pL, pR) = seg[i];
			if(i > 0) {
				tie(qL, qR) = seg[i - 1];
				int val = ord[pL], pos = lower_bound(ord + qL, ord + qR + 1, val) - ord;
				addL[i] = pos - qL;
			} else {
				addL[i] = 0;
			}
			if(i + 1 < tot) {
				tie(qL, qR) = seg[i + 1];
				int val = ord[pR], pos = lower_bound(ord + qL, ord + qR + 1, val) - ord;
				addR[i] = qR - pos + 1;
			} else {
				addR[i] = 0;
			}
		}
		int ans = n, cnt = 0;
		for(int i = 0, j = 0; i < tot; ++i) {
			for( ; j < tot && (i == j || ord[seg[j - 1].second] < ord[seg[j].first]); ++j)
				cnt += seg[j].second - seg[j].first + 1;
			ans = min(ans, n - cnt - addL[i] - addR[j - 1]);
			cnt -= seg[i].second - seg[i].first + 1;
		}
		for(int i = 1; i < tot; ++i) {
			int pL, pR, qL, qR;
			tie(pL, pR) = seg[i];
			tie(qL, qR) = seg[i - 1];
			for(int j = pL; j <= pR; ++j) {
				// [qL, pos-1] + [j, pR]
				int val = ord[j], pos = lower_bound(ord + qL, ord + qR + 1, val) - ord;
				int cnt = (pos - qL) + (pR - j + 1);
				ans = min(ans, n - cnt);
			}
		}
		printf("%d\n", ans);
		// printf("Case #%d:");
	}

	return 0;
}