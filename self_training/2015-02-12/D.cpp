#include <cstdio>
int n, now, tot;
long long k, a, sum;
int main()
{
	scanf("%d%I64d", &n, &k);
	tot = n;
	for(int i = 1; i <= n; ++i)
	{
		++now;
		scanf("%I64d", &a);
		if(sum - (now - 1) * (tot - now) * a < k)
		{
			printf("%d\n", i);
			--now;
			--tot;
		}
		else
			sum += (now - 1) * a;
	}
	return 0;
}
