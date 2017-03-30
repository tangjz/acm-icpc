#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
const int maxn = 501, delta = 10, diff = 20, maxv = (1 << 8) - 1, val[2] = {0, maxv};
int n, m, a[maxn][maxn], b[maxn][maxn], d[maxn][maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%d", a[i] + j);
	srand(time(NULL));
	while(1)
	{
		memcpy(d, a, sizeof a);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				b[i][j] = val[(rand() & maxv) < d[i][j]];
				int dt = b[i][j] - d[i][j];
				if(i < n)
				{
					if(j < m)
					{
						d[i][j + 1] -= dt >> 1;
						d[i + 1][j] -= dt - (dt >> 1);
					}
					else
						d[i + 1][j] -= dt;
				}
				else if(j < m)
					d[i][j + 1] -= dt;
			}
		bool flag = 1;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= m; ++j)
			{
				int xL = i - delta < 1 ? 1 : i - delta, xR = i + delta < n ? i + delta : n;
				int yL = j - delta < 1 ? 1 : j - delta, yR = j + delta < m ? j + delta : m;
				int cnt = 0, sum = 0;
				for(int x = xL; x <= xR; ++x)
					for(int y = yL; y <= yR; ++y)
					{
						++cnt;
						sum += b[x][y] - a[x][y];
					}
				if(sum < 0)
					sum = -sum;
				if(sum > diff * cnt)
				{
					flag = 0;
					break;
				}
			}
			if(!flag)
				break;
		}
		if(flag)
			break;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			printf("%d%c", b[i][j], " \n"[j == m]);
	return 0;
}
