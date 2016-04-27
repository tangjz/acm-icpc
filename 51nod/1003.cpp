#include <cstdio>
int n, ans;
int main()
{
	for(scanf("%d", &n); n; ans += n /= 5);
	printf("%d\n", ans);
	return 0;
}
