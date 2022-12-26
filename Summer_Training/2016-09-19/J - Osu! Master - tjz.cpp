#include <stdio.h>
int n, p, x, ans;
char op[2];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		ans = 0;
		p = 0;
		while(n--)
		{
			scanf("%s", op);
			if(op[0] == 'S')
			{
				if(p != 0)
					++ans;
				p = -1;
			}
			else
			{
				scanf("%d", &x);
				if(x != p + 1)
					++ans;
				p = x;
			}
		}
		if(p != 0)
			++ans;
		printf("%d\n", ans);
	}
	return 0;
}
