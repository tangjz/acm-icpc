#include <bits/stdc++.h>
const int maxn = 20, ans[] = {0, 1, 1, 2, 3, 0, 3, 3, 1, 4, 0, 4, 4, 3, 2, 0, 2, 2, 4, 1};
int t, n;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", ans[n % maxn]);
	}
	return 0;
}
