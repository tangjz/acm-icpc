#include <stdio.h>
#include <algorithm>
const int maxn = 15001;
int n, a[maxn], b[maxn];
double ans;
bool cmp(int const &x, int const &y) {
	return a[x] < a[y];
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		b[i] = i;
	}
	std::sort(b, b + n, cmp);
	for(int i = 0; i < n; ++i) {
		a[b[i]] = i;
		b[i] = 0;
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0, k = a[i]; j < i; ++j)
			a[j] > k && (++b[a[j] - k]);
	for(int i = 1; i < n; ++i)
		ans += (b[i] << 1) / (i + 1.0);
	printf("%.6f\n", ans);
	return 0;
}
