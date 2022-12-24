#include <cmath>
#include <cstdio>
typedef long long LL;
int n;
bool is_triple(int x)
{
	int a = sqrt(x);
	for( ; ((a + 1) * (a + 2) >> 1) <= x; ++a);
	for( ; (a * (a + 1) >> 1) > x; --a);
	return (a * (a + 1) >> 1) == x;
}
bool is_square(LL x)
{
	LL a = sqrt(x);
	for( ; (a + 1) * (a + 1) <= x; ++a);
	for( ; a * a > x; --a);
	return a * a == x;
}
int main()
{
	while(scanf("%d", &n) == 1)
		puts(n == 1 ? "0" : is_triple(n) || is_triple(n - 1) || is_square(n * (n + 1LL) >> 1) || is_square((n * (n + 1LL) >> 1) - 1) ? "1" : "2");
	return 0;
}
