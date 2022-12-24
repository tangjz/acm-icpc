#include <stdio.h>
const int maxn = 50001;
int n, x;
long long sum, ans;
int main() {
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &x);
		sum += x;
		ans > sum && (ans = sum);
	}
	printf("%lld\n", -ans);
	return 0;
}
