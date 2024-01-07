#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
	int m;
	LL n;
	scanf("%lld%d", &n, &m);
	while(m--) {
		LL x1, y1, x2, y2, ans = 0;
		scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
		ans += max(min(x2, y2) - max(x1, y1) + 1, 0LL);
		tie(x1, x2) = make_pair(n - 1 - x2, n - 1 - x1);
		ans += max(min(x2, y2) - max(x1, y1) + 1, 0LL);
		if(n & 1) {
			LL half = n >> 1;
			ans -= x1 <= half && half <= x2 && y1 <= half && half <= y2;
		}
		printf("%lld\n", ans);
	}
	return 0;
}