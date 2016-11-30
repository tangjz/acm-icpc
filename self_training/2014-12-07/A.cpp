#include <cstdio>
int n, x, y, w, now, day;
int main()
{
	while(scanf("%d%d%d%d", &n, &x, &y, &w) == 4)
	{
		now = day = 0;
		while(1)
		{
			now += x + y;
			if(w >= 6)
				now += x;
			++day;
			if(now >= n)
				break;
			++w;
			if(w > 7)
				w = 1;
		}
		printf("%d %d\n", day, w);
	}
	return 0;
}
