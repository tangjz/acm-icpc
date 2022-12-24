#include <bits/stdc++.h>
int main() {
	int t, n, x, y;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &x);
		if(n > 1) {
			scanf("%d", &y);
			y /= std::__gcd(x, y);
		} else {
			y = 1;
		}
		for(int i = 2; i < n; ++i) {
			scanf("%d", &x);
			y /= std::__gcd(x, y);
		}
		puts(y == 1 ? "YES" : "NO");
	}
	return 0;
}