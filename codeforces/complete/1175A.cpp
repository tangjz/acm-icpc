#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		long long n, k, ans = -1;
		scanf("%lld%lld", &n, &k);
		while(n) {
			ans += n % k + 1;
			n /= k;
		}
		printf("%lld\n", ans);
	}
	return 0;
}