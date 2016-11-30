#include <stdio.h>
int t, n;
long long sum1(int x)
{
	return x * (x + 1LL) >> 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		--n;
		printf("%lld\n", sum1(n / 3) * 3 + sum1(n / 5) * 5 - sum1(n / 15) * 15);
	}
	return 0;
}
