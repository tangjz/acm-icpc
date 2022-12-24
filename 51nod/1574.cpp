#include <stdio.h>
#include <algorithm>
const int maxn = 200010;
int n, f[maxn], g[maxn];
long long sum;
int main() {
	scanf("%d", &n);
	for(int i = 1, j; i <= n; ++i) {
		scanf("%d", &j);
		f[j] = i;
	}
	for(int i = 1, j; i <= n; ++i) {
		scanf("%d", &j);
		g[j] = i;
	}
	for(int i = n; i >= 1; --i)
		sum += std::abs(f[i] - g[i]);
	printf("%lld\n", sum >> 1);
	return 0;
}
