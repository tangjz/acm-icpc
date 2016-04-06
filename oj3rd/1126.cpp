#include <cstdio>
#include <cstring>
int n, x, y, now, mat[1001][1001], ans;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		x = y = now = ans = 0;
		memset(mat, 0, sizeof mat);
		mat[x][y] = ++now;
		while(now < n * n)
		{
			while(y + 1 < n && !mat[x][y + 1])
				mat[x][++y] = ++now;
			while(x + 1 < n && !mat[x + 1][y])
				mat[++x][y] = ++now;
			while(y - 1 >= 0 && !mat[x][y - 1])
				mat[x][--y] = ++now;
			while(x - 1 >= 0 && !mat[x - 1][y])
				mat[--x][y] = ++now;
		}
		for(x = 0; x < n; ++x)
		{
			ans += mat[x][x];
			for(y = 0; y < n; ++y)
				printf("%d ", mat[x][y]);
			putchar('\n');
		}
		printf("%d\n", ans);
	}
	return 0;
}
