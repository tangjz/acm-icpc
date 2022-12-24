#include <bits/stdc++.h>
const int maxn = 100001;
int t, n, x, ans;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		ans = 0;
		while(n--) {
			scanf("%d", &x);
			ans ^= x << 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
