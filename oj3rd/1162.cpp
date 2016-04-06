#include <cstdio>
int n, x, r, c;
char str[1010], ans[101][1010];
int main()
{
	while(scanf("%d%d", &n, &x) == 2)
	{
		r = c = 0;
		while(n--)
		{
			scanf("%s", str);
			for(int i = 0; str[i]; ++i)
			{
				ans[r++][c] = str[i];
				if(r == x)
				{
					r = 0;
					++c;
				}
			}
		}
		for(int i = 0; i < x; ++i)
		{
			ans[i][c + (i < r)] = '\0';
			puts(ans[i]);
		}
		puts("");
	}
	return 0;
}
