#include <cmath>
#include <cstdio>
int R, M, Y, ans;
int main()
{
	scanf("%d%d%d", &R, &M, &Y);
	ans = (int)(M * pow(1 + R * 0.01, Y) + 1e-8);
	printf("%d\n", ans);
	return 0;
}
