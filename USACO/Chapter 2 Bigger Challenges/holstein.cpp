/*
ID: tangjin2
LANG: C++
TASK: holstein
*/
#include <cstdio>
int v, goal[25], g, num[15][25], ans, tmp[15], output[15];
void dfs(int dep, int from)
{
	if(dep > ans) return;
	for(int i = from, j; i < g; ++i)
	{
		for(j = 0; j < v; ++j) goal[j] -= num[i][j];
		tmp[dep - 1] = i;
		for(j = 0; j < v; ++j) if(goal[j] > 0) break;
		if(j < v) dfs(dep + 1, i + 1);
		else if(dep < ans || !output[0])
		{
			ans = dep;
			for(j = 0; j < ans; ++j) output[j] = tmp[j] + 1;
		}
		for(j = 0; j < v; ++j) goal[j] += num[i][j];
	}
}
int main()
{
	freopen("holstein.in", "r", stdin);
	freopen("holstein.out", "w", stdout);
	int i, j;
	scanf("%d", &v);
	for(i = 0; i < v; ++i) scanf("%d", &goal[i]);
	scanf("%d", &g);
	for(i = 0; i < g; ++i)
		for(j = 0; j < v; ++j) scanf("%d", &num[i][j]);
	ans = g;
	dfs(1, 0);
	printf("%d", ans);
	for(i = 0; i < ans; ++i) printf(" %d", output[i]);
	putchar('\n');
	fclose(stdin);
	fclose(stdout);
	return 0;
}
