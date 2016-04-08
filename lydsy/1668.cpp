#include <cstdio>
int r, c, num[101][101], f[101][101];
int main()
{
	scanf("%d%d", &r,  &c);
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j) scanf("%d", &num[i][j]);
	f[0][0] = num[0][0];
	for(int j = 1; j < c; ++j)
		for(int i = j < r ? j : r; i >= 0; --i)
		{
			if(i - 1 >= 0 && f[i - 1][j - 1] > f[i][j]) f[i][j] = f[i - 1][j - 1];
			if(f[i][j - 1] > f[i][j]) f[i][j] = f[i][j - 1];
			if(i + 1 < r && f[i + 1][j - 1] > f[i][j]) f[i][j] = f[i + 1][j - 1];
			f[i][j] += num[i][j];
		}
	printf("%d\n", f[r - 1][c - 1]);
 	return 0;
}
