#include <cstdio>
int ans = 1;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main()
{
	for(int i = 2; i <= 20; ++i) ans *= i / gcd(ans, i);
	printf("%d\n", ans);
	return 0;
}
