#include <bits/stdc++.h>
const int maxn = (int)1e5 + 1;
int n, a[maxn], f[maxn], que[maxn], L, R;
int main() {
	scanf("%d", &n);
	for(int i = n; i >= 1; --i)
		scanf("%d", a + i);
	que[R++] = 0;
	for(int i = 1; i <= n; ++i) {
		a[i] += a[i - 1];
		for( ; L + 1 < R && a[i] - a[que[L + 1]] >= a[que[L + 1]] - a[f[que[L + 1]]]; ++L);
		f[i] = que[L];
		for( ; L < R && a[i] + (a[i] - a[f[i]]) <= a[que[R - 1]] + (a[que[R - 1]] - a[f[que[R - 1]]]); --R);
		que[R++] = i;
	}
	int ans = 0;
	for(int i = n; i > 0; i = f[i], ++ans);
	printf("%d\n", ans);
	return 0;
}