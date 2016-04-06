#include <cstdio>
int n, m, ans, out[3000][2];
char map[60][60];
int main()
{
	freopen("crosswords.in", "r", stdin);
	freopen("crosswords.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%s", map[i] + 1);
	for(int i = 0; i <= m + 2; ++i)
		map[0][i] = map[n + 1][i] = map[n + 2][i] = '#';
	for(int i = 1; i <= n; ++i)
		map[i][0] = map[i][m + 1] = map[i][m + 2] = '#';
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(map[i][j] == '.' && map[i][j - 1] == '#' && map[i][j + 1] == '.' && map[i][j + 2] == '.'
			|| map[i][j] == '.' && map[i - 1][j] == '#' && map[i + 1][j] == '.' && map[i + 2][j] == '.')
			{
				out[ans][0] = i;
				out[ans][1] = j;
				++ans;
			}
	printf("%d\n", ans);
	for(int i = 0; i < ans; ++i)
		printf("%d %d\n", out[i][0], out[i][1]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
