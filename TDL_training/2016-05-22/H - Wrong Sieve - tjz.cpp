#include <cstdio>
typedef long long LL;
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		LL n;
		scanf("%lld", &n);
		for(int i = 2; i <= n; ++i)
			if(n % i)
				n -= n / i;
			else
			{
				n = -1;
				break;
			}
		printf("%d\n", n);
	}
	return 0;
}
