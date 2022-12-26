/*
 * 据说是logN取上整
 */
#include <cstdio>
long long n, x = 1;
int ans = 0;
int main()
{
	scanf("%lld", &n);
	while(x < n) x <<= 1, ++ans;
	printf("%d\n", ans);
	return 0;
}
