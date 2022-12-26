#include <cmath>
#include <stdio.h>
int main() {
	int t, n, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		m = sqrt(((n - 1) << 2) + 0.25) - 0.5;
		for( ; ((m * (m + 1)) >> 1) < n; ++m);
		for( ; ((m * (m + 1)) >> 1) >= n; --m);
		puts(((m * (m + 1)) >> 1) == n - 1 ? "1" : "0");
	}
	return 0;
}
