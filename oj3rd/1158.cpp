#include <cstdio>
const int maxn = 1001;
int m, n;
void scan(int &x)
{
	static int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0';
}
int main()
{
	while(scanf("%d%d", &m, &n) == 2)
	{
		while(m--)
		{
			int pos = 1, min, x;
			scan(min);
			for(int i = 2; i <= n; ++i)
			{
				scan(x);
				if(x < min)
				{
					pos = i;
					min = x;
				}
			}
			printf("%d ", pos);
		}
		putchar('\n');
	}
	return 0;
}
