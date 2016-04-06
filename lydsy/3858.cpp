#include <cstdio>
int t;
long long x, k;
int main()
{
	while(scanf("%lld%lld", &x, &k) == 2 && x + k)
	{
		for(long long i = 2; i <= k; ++i)
		{
			long long tmp = (x - 1) / i + 1;
			if(tmp <= i)
			{
				x = tmp * k;
				break;
			}
			x = tmp * i;
		}
		printf("Case #%d: %lld\n", ++t, x);
	}
	return 0;
}
