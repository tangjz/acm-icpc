#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1;
const int mod = (int)1e9 + 7;

struct Info {
	int fir, las, cnt;
};

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
		static Info seg[maxn];
		for(int i = 0; i < n; ++i)
			if(!i || a[ord[i - 1]] != a[ord[i]]) {
				seg[tot++] = (Info){ord[i], ord[i], 1};
			} else {
				seg[tot - 1].las = ord[i];
				++seg[tot - 1].cnt;
			}
		int ans = n, cnt = 0;
		for(int i = 0, j = 0; i < n; ++i) {
			if(i == j)
				cnt += seg[j++].cnt;
			for( ; j < n && seg[j - 1].las < seg[j].fir; cnt += seg[j++].cnt);
			ans = min(ans, n - cnt);
			cnt -= seg[i].cnt;
		}
		printf("%d\n", ans);
		// printf("Case #%d:");
	}

	return 0;
}
