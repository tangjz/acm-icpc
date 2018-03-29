#include <bits/stdc++.h>
using namespace std;
int n, x, ans;
int main() {
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &x);
		ans += abs(x);
	}
	printf("%d\n", ans);
	return 0;
}
