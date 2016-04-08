#include <cstdio>
char ch[113][78];
int r, c, step, ans[8702][2];
bool dfs(int x, int y, int dep)
{
	if(x == r - 1 && y == c - 1) { step = dep; return true; }
	if(dep >= 8702 || x < 0 || x >= r || y < 0 || y >= c || ch[x][y] != '.') return false;
	ans[dep][0] = x + 1, ans[dep][1] = y + 1;
	ch[x][y] = '@';
	return dfs(x + 1, y, dep + 1) || dfs(x - 1, y, dep + 1) || dfs(x, y + 1, dep + 1) || dfs(x, y - 1, dep + 1);
}
int main()
{
	scanf("%d%d", &r, &c);
	for(int i = 0; i < r; ++i) scanf("%s", ch[i]);
	dfs(0, 0, 0);
	for(int i = 0; i < step; ++i) printf("%d %d\n", ans[i][0], ans[i][1]);
	printf("%d %d\n", r, c);
	return 0;
}

