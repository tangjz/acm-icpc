#include <cstdio>
#include <cstring>
const int maxn = 101, maxt = 101, maxm = 101;
int n, t, f[maxn][maxt];
int max(int x, int y)
{
	return x < y ? y : x;
}
int main()
{
	while(scanf("%d%d", &n, &t) == 2)
	{
		for(int i = 1; i <= n; ++i)
		{
			int m, s, c, w;
			scanf("%d%d", &m, &s);
			if(s)
				memcpy(f[i], f[i - 1], sizeof f[0]);
			else
				memset(f[i], -1, sizeof f[0]);
			while(m--)
			{
				scanf("%d%d", &c, &w);
				for(int j = t; j >= c; --j)
					if(!s)//at least
					{
						int tmp = max(f[i - 1][j - c], f[i][j - c]);
						if(tmp != -1 && f[i][j] < tmp + w)
							f[i][j] = tmp + w;
					}
					else if(s == 1)//at most
					{
						if(f[i - 1][j - c] != -1 && f[i][j] < f[i - 1][j - c] + w)
							f[i][j] = f[i - 1][j - c] + w;
					}
					else
					{
						int tmp = max(f[i - 1][j - c], f[i][j - c]);
						if(tmp != -1 && f[i][j] < tmp + w)
							f[i][j] = tmp + w;
					}
			}
		}
		printf("%d\n", f[n][t]);
	}
	return 0;
}
