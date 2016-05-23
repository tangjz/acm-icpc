#include <stdio.h>
int t, a, b, d, n, x, y, ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &a, &b, &d, &n);
		x = a * b / 10;
		y = a * b % 10;
		ans = 0;
		if(x + y < 10)
		{
			if(x > 0 && x == d)
				++ans;
			if(n > 1 && x + y == d)
				ans += n - 1;
			if(y == d)
				++ans;
		}
		else if(n > 1)
		{
			int p = x + 1;
			int q = x + y - 9;
			int r = x + y - 10;
			int s = y;
			if(p == d)
				++ans;
			if(q == d)
				ans += n - 2;
			if(r == d)
				++ans;
			if(s == d)
				++ans;
		}
		else
		{
			if(x == d)
				++ans;
			if(y == d)
				++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
