#include <cstdio>
const int maxn = 11;
int n, tot;
char mat[2][maxn][maxn], enc[maxn * maxn], dec[maxn * maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%s", mat[0][i]);
	scanf("%s", enc);
	for(int t = 0; t < 4; ++t)
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				if(mat[t & 1][i][j] == '.')
				{
					if(dec[i * n + j])
					{
						puts("invalid grille");
						return 0;
					}
					dec[i * n + j] = enc[tot++];
				}
				mat[~t & 1][j][n - 1 - i] = mat[t & 1][i][j];
			}
	puts(tot == n * n ? dec : "invalid grille");
	return 0;
}
