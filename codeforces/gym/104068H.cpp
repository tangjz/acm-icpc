#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e6 + 1;

void solve() {
	int n;
	static int a[maxn];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	LL ans = 0;
	for(int L = 0, R = n - 1; L < R; ++L, --R)
		if(R - L + 1 == 3) {
			ans = max(ans, (LL)a[R - 1] * a[R]);
		} else {
			ans = max(ans, (LL)a[L] * a[R]);
		}
	printf("%lld\n", ans);
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