#include <cstdio>
int t, h, a, b, k;
int main()
{
	while(scanf("%d%d%d%d", &h, &a, &b, &k) == 4 && h + a + b + k)
		printf("Case #%d: %s\n", ++t, h <= a || h - (long long)k * (a - b) - b <= 0 || (long long)k * (b - a) + b < 0 ? "YES" : "NO");
	return 0;
}
