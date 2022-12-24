#include <cmath>
#include <cstdio>
typedef long long LL;
int t, m;
LL n;
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%lld", &n);
		m = (int)floor(sqrt((n << 1) + 0.25) - 0.5);
		for( ; (m * (m + 1LL)) >> 1 <= n; ++m);
		for( ; (m * (m + 1LL)) >> 1 > n; --m);
		printf("Case #%d: %lld\n", Case, (m * (m + 1LL)) >> 1);
	}
	return 0;
}
