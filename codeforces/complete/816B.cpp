#include <cstdio>
const int maxn = 200001;
int n, m, q, a[maxn + 2];
int main() {
	scanf("%d%d%d", &n, &m, &q);
	while(n--) {
		int l, r;
		scanf("%d%d", &l, &r);
		++a[l];
		--a[r + 1];
	}
	for(int i = 1; i < maxn; ++i)
		a[i] += a[i - 1];
	for(int i = 1; i < maxn; ++i)
		a[i] = (a[i] >= m) + a[i - 1];
	while(q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", a[r] - a[l - 1]);
	}
	return 0;
}
