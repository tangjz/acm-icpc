#include <bits/stdc++.h>
using namespace std;
const int lowv = 1, uppv = (int)1e6;
int n, x, ans;
int main() {
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &x);
		ans = max(ans, min(x - lowv, uppv - x));
	}
	printf("%d\n", ans);
	return 0;
}
