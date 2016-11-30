#include <cstdio>
#include <cstring>
const int maxm = 101, maxs = 101, maxk = 101;
int n, m, t, s, f[maxm][maxs];
int main()
{
	while(scanf("%d%d%d%d", &n, &m, &t, &s) == 4)
	{
		memset(f, 0, sizeof f);
		for(int i = 0, a, b; i < t; ++i)
		{
			scanf("%d%d", &a, &b);
			for(int j = b; j <= m; ++j)
				for(int k = 1; k <= s; ++k)
					if(f[j][k] < f[j - b][k - 1] + a)
						f[j][k] = f[j - b][k - 1] + a;
		}
		int ans = -1;
		for(int i = 0; i <= m && ans == -1; ++i)
			for(int j = 0; j <= s; ++j)
				if(f[i][j] >= n)
				{
					ans = m - i;
					break;
				}
		printf("%d\n", ans);
	}
	return 0;
}
