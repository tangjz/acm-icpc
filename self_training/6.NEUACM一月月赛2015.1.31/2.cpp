#include <cstdio>
int n, t, c, x, lpos, ans;
int main()
{
	while(scanf("%d%d%d", &n, &t, &c) == 3)
	{
		lpos = ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", &x);
			if(x <= t && !lpos)
				lpos = i;
			else if(x > t && lpos)
			{
				if(i - lpos >= c)
					ans += i - lpos - c + 1;
				lpos = 0;
			}
		}
		if(lpos && n + 1 - lpos >= c)
			ans += n + 1 - lpos - c + 1;
		printf("%d\n", ans);
	}
	return 0;
}
