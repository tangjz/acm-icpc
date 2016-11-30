#include <stdio.h>
typedef long long LL;
LL sqr(int x)
{
	return (LL)x * x;
}
int sum1(int x)
{
	return x * (x + 1) >> 1;
}
LL sum2(int x)
{
	return x * (x + 1) * ((x << 1) + 1LL) / 6;
}
int main()
{
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%lld\n", sqr(sum1(n)) - sum2(n));
	}
	return 0;
}
