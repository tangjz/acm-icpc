/*
 * 经典dp问题? 令f[i,j]表示演奏第i首歌时是否可以有音量j，转移不用多说 
 */
#include <cstdio>
const int maxn = 51, maxlim = 1010;
int n, sta, lim, c;
bool f[maxn][maxlim];
int main()
{
	scanf("%d%d%d", &n, &sta, &lim);
	f[0][sta] = 1;
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &c);
		for(int j = 0; j <= lim; ++j)
			if(f[i][j])
			{
				if(j + c <= lim) f[i + 1][j + c] = 1;
				if(j >= c) f[i + 1][j - c] = 1;
			}
	}
	for(int i = lim; i >= 0; --i)
		if(f[n][i])
		{
			printf("%d\n", i);
			return 0;
		}
	puts("-1");
	return 0;
}
