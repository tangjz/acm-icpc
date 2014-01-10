/*
ID: tangjin2
LANG: C++
TASK: castle
*/
#include <cstdio>
int m, n, room[51][51], num[51][51], sum, cnt[2501], tmp1, tmp2, max_castle, max_delete;
char flag;
void dfs(int x, int y)
{
	if(x < 1 || x > n || y < 1 || y > m || num[x][y]) return;
	num[x][y] = sum;
	++cnt[sum];
	int tmp = 15 - room[x][y];
	if(tmp & 1) dfs(x, y - 1);
	if(tmp & 2) dfs(x - 1, y);
	if(tmp & 4) dfs(x, y + 1);
	if(tmp & 8) dfs(x + 1, y);
}
int main()
{
	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);
	int i, j;
	scanf("%d%d", &m, &n);
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= m; ++j) scanf("%d", &room[i][j]);
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= m; ++j)
			if(!num[i][j])
			{
				++sum;
				dfs(i, j);
				if(cnt[sum] >= max_castle) max_castle = cnt[sum];
			}
	for(i = 1; i <= m; ++i)
		for(j = n; j > 1 || n == 1 && j > 0; --j)
		{
			if(j >= 2 && num[j][i] != num[j - 1][i] && cnt[num[j][i]] + cnt[num[j - 1][i]] > max_delete)
			{
				tmp1 = j, tmp2 = i;
				flag = 'N';
				max_delete = cnt[num[j][i]] + cnt[num[j - 1][i]];
			}
			if(i < m && num[j][i] != num[j][i + 1] && cnt[num[j][i]] + cnt[num[j][i + 1]] > max_delete)
			{
				tmp1 = j, tmp2 = i;
				flag = 'E';
				max_delete = cnt[num[j][i]] + cnt[num[j][i + 1]];
			}
		}
	printf("%d\n%d\n%d\n%d %d %c\n", sum, max_castle, max_delete, tmp1, tmp2, flag);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
