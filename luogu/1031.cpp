#include <cstdio>
int n, a[101], x, ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%d", &a[i]), x += a[i];
	x /= n;
	for(int i = 0; i < n - 1; ++i) ans += a[i] != x, a[i + 1] += a[i] - x;
	printf("%d\n", ans);
}
