#include <cstdio>
const int maxn = 201, INF = 0x3f3f3f3f, d[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
int n, mat[maxn][maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%d", &mat[i][j]);
	ans = -INF;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			for(int o = 0; o < 4; ++o)
			{
				int now = 0;
				for(int k = 0, x = i, y = j; k < n; ++k)
				{
					now = (now > 0 ? now : 0) + mat[x][y];
					if(ans < now)
						ans = now;
					x += d[o][0];
					if(x == n)
						x = 0;
					y += d[o][1];
					if(y == n)
						y = 0;
					else if(y == -1)
						y = n - 1;
				}
			}
	printf("%d\n", ans);
	return 0;
}
