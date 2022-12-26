#include <cstdio>
#include <algorithm>
using namespace std;
const int score[9][9] = {
{6, 6, 6, 6, 6, 6, 6, 6, 6},
{6, 7, 7, 7, 7, 7, 7, 7, 6},
{6, 7, 8, 8, 8, 8, 8, 7, 6},
{6, 7, 8, 9, 9, 9, 8, 7, 6},
{6, 7, 8, 9, 10, 9, 8, 7, 6},
{6, 7, 8, 9, 9, 9, 8, 7, 6},
{6, 7, 8, 8, 8, 8, 8, 7, 6},
{6, 7, 7, 7, 7, 7, 7, 7, 6},
{6, 6, 6, 6, 6, 6, 6, 6, 6}};
int n = 0, sum = 0, tmp = 0, ans = 0;
bool r[9][10] = {}, c[9][10] = {}, rc[9][10] = {};
pair<int, int> dfs_list[57];
int Time;
void dfs(int dep)
{
	if(Time == 10000000) return; ++Time;
	if(!dep) { if(tmp > ans) ans = tmp; return; }
	int x = dfs_list[dep - 1].first, y = dfs_list[dep - 1].second;
	int z = x / 3 * 3 + y / 3;
	for(int i = 1; i <= 9; ++i)
		if(!r[x][i] && !c[y][i] && !rc[z][i])
		{
			r[x][i] = c[y][i] = rc[z][i] = true;
			tmp += i * score[x][y];
			dfs(dep - 1);
			r[x][i] = c[y][i] = rc[z][i] = false;
			tmp -= i * score[x][y];
		}
}
int main()
{
	int x;
	for(int i = 0; i < 9; ++i)
		for(int j = 0; j < 9; ++j)
		{
			scanf("%d", &x);
			if(x)
			{
				sum += x * score[i][j];
				r[i][x] = c[j][x] = rc[i / 3 * 3 + j / 3][x] = true;
			}
			else dfs_list[n++] = make_pair(i, j);
		}
	dfs(n);
	if(!ans) printf("-1\n");
	else printf("%d\n", sum + ans);
	return 0;
}
