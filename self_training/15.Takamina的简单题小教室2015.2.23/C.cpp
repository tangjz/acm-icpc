#include <cstdio>
int l, x, ans, sum;
int main()
{
	while(scanf("%d%d", &l, &ans) == 2)
	{
		sum = 1;
		while(--l)
		{
			scanf("%d", &x);
			if(x == ans)
				++sum;
			else if(sum > 0)
				--sum;
			else
			{
				ans = x;
				sum = 1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
