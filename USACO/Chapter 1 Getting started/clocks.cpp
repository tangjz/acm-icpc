/*
ID: tangjin2
LANG: C++
TASK: clocks
*/
#include <cstdio>
const int check[9][9] = {
{1, 1, 0, 1, 1, 0, 0, 0, 0},
{1, 1, 1, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 0, 1, 1, 0, 0, 0},
{1, 0, 0, 1, 0, 0, 1, 0, 0},
{0, 1, 0, 1, 1, 1, 0, 1, 0},
{0, 0, 1, 0, 0, 1, 0, 0, 1},
{0, 0, 0, 1, 1, 0, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 1, 1, 1},
{0, 0, 0, 0, 1, 1, 0, 1, 1}};
int data[9], way[1000], ans[1001], len = 1000, num[9];
void dfs(int dep)
{
	if(dep > len) return;
	int x, y;
	for(x = 0; x < 9; ++x) if(data[x]) break;
	if(x >= 9)
	{
		len = dep - 1;
		for(x = 1; x <= len; ++x) ans[x] = way[x] + 1;
	}
	else
		for(x = way[dep - 1]; x < 9; ++x)
		{
			if(num[x] == 3) continue;
			for(y = 0; y < 9; ++y) data[y] = (data[y] + check[x][y]) & 3;
			++num[x];
			way[dep] = x;
			dfs(dep + 1);
			for(y = 0; y < 9; ++y) data[y] = (data[y] - check[x][y] + 4) & 3;
			--num[x];
		}
}
int main()
{
	freopen("clocks.in", "r", stdin);
	freopen("clocks.out", "w", stdout);
	int i;
	for(i = 0; i < 9; ++i)
	{
		scanf("%d", &data[i]);
		data[i] = (data[i] / 3) & 3;
	}
	dfs(1);
	for(i = 1; i < len; ++i) printf("%d ", ans[i]);
	printf("%d\n", ans[len]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
