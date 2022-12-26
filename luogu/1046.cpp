#include <cstdio>
int a[11], ans;
int main()
{
	for(int i = 0; i < 11; ++i) scanf("%d", &a[i]);
	a[10] += 30;
	for(int i = 0; i < 10; ++i) ans += a[i] <= a[10];
	printf("%d\n", ans);
}
