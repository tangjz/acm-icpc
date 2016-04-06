#include <cstdio>
const int maxn = 510, dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int t, x, y, o, xmin, xmax, ymin, ymax;
char str[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%s", str);
		x = y = o = xmin = xmax = ymin = ymax = 0;
		for(int i = 0; str[i]; ++i)
		{
			switch(str[i])
			{
				case 'F' : x += dx[o]; y += dy[o]; break;
				case 'B' : x -= dx[o]; y -= dy[o]; break;
				case 'L' : o = (o + 3) & 3; break;
				case 'R' : o = (o + 1) & 3; break;
			}
			if(x < xmin)
				xmin = x;
			else if(xmax < x)
				xmax = x;
			if(y < ymin)
				ymin = y;
			else if(ymax < y)
				ymax = y;
		}
		printf("%d\n", (xmax - xmin) * (ymax - ymin));
	}
	return 0;
}
