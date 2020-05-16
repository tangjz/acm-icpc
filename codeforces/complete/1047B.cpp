#include <bits/stdc++.h>
using namespace std;
int n, x, y, ans;
int main() {
	scanf("%d", &n);
	while(n--) {
		scanf("%d%d", &x, &y);
		ans = max(ans, x + y);
	}
	printf("%d\n", ans);
	return 0;
}
