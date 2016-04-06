#include <cstdio>
const int maxn = 10000001;
int n, m, t, a, b, c, d, e;
char str[maxn];
int main()
{
	scanf("%d%d%d", &n, &m, &t);
	while(t--)
	{
		a = b = c = d = e = 0;
		if((n < m ? n : m) < 3)
		{
			for(int i = 0; i < n; ++i)
			{
				scanf("%s", str);
				for(int j = 0; j < m; ++j)
					a |= str[j] == '#';
			}
			puts(!a ? "YES" : "NO");
			continue;
		}
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", str);
			for(int j = 0; j < m; ++j)
			{
				int o = str[j] == '#';
				if(i % 3 != 1)
					a ^= o;
				if(i % 3 != 0)
					b ^= o;
				if(j % 3 != 1)
					c ^= o;
				if(j % 3 != 0)
					d ^= o;
				if(m == 3)
				{
					if(i % 6 >= 3 && (j == 0 || j == 2) || i % 3 == 1 && j == 1)
						e ^= o;
				}
				else if(n == 3)
				{
					if((i == 0 || i == 2) && j % 6 >= 3 || i == 1 && j % 3 == 1)
						e ^= o;
				}
			}
		}
		puts(!a && !b && !c && !d && !((n < m ? n : m) == 3 && e) ? "YES" : "NO");
	}
	return 0;
}
