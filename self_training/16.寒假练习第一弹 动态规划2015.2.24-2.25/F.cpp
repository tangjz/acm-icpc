#include <cstdio>
#include <cstring>
const int maxv = 50001;
int n, v, f[maxv];
int main()
{
	while(scanf("%d%d", &v, &n) == 2)
	{
		memset(f, 0, sizeof f);
		v /= 100;
		while(n--)
		{
			int c1, w1, c2, w2, type;
			scanf("%d%d%d%d%d", &c1, &w1, &c2, &w2, &type);
			c1 /= 100;
			c2 /= 100;
			if(type == 1)
			{
				c1 += c2;
				w1 += w2;
				for(int i = v; i >= c1; --i)
					if(f[i] < f[i - c1] + w1)
						f[i] = f[i - c1] + w1;
			}
			else
			{
				if(type == 3)
				{
					c2 += c1;
					w2 += w1;
				}
				for(int i = v; i >= 0; --i)
				{
					int tmp = f[i];
					if(i >= c1 && tmp < f[i - c1] + w1)
						tmp = f[i - c1] + w1;
					if(i >= c2 && tmp < f[i - c2] + w2)
						tmp = f[i - c2] + w2;
					f[i] = tmp;
				}
			}
		}
		printf("%d\n", f[v]);
	}
	return 0;
}
