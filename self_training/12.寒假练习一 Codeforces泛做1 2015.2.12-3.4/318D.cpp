#include <cstdio>
#include <cstring>
const int maxs = 141, delta = 70, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
int n, q, f[maxs][maxs], g[maxs][maxs];
int main()
{
	scanf("%d%d", &n, &q);
	f[delta][delta] = n;
	while(1)
	{
		bool flag = 0;
		for(int i = 0; i < maxs; ++i)
			for(int j = 0; j < maxs; ++j)
				if(f[i][j] >= 4)
				{
					for(int k = 0; k < 4; ++k)
						g[i + dx[k]][j + dy[k]] += f[i][j] >> 2;
					f[i][j] &= 3;
				}
		for(int i = 0; i < maxs; ++i)
			for(int j = 0; j < maxs; ++j)
			{
				f[i][j] += g[i][j];
				g[i][j] = 0;
				if(f[i][j] >= 4)
					flag = 1;
			}
		if(!flag)
			break;
	}
	while(q--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(x + delta >= 0 && x + delta < maxs && y + delta >= 0 && y + delta < maxs)
			printf("%d\n", f[x + delta][y + delta]);
		else
			puts("0");
	}
	return 0;
}
