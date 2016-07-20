#include <cstdio>
#include <cstring>
const int maxn = 11;
int n, tot;
char mat[2][maxn][maxn], enc[maxn * maxn], dec[maxn * maxn];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n; ++i)
			scanf("%s", mat[0][i]);
		scanf("%s", enc);
		tot = 0;
		memset(dec, 0, (n * n + 1) * sizeof(char));
		for(int t = 0; t < 4; ++t)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
				{
					if(mat[t & 1][i][j] == '.')
					{
						if(dec[i * n + j])
						{
							tot = -1;
							goto finished;
						}
						dec[i * n + j] = enc[tot++];
					}
					mat[~t & 1][j][n - 1 - i] = mat[t & 1][i][j];
				}
	finished:
		puts(tot == n * n ? dec : "invalid grille");
	}
	return 0;
}
