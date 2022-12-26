/*
 * 迭代加深搜索
 */
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF = ~0u >> 1, maxstep = 16, f[8][2] = {{2, 1}, {2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};
const char end[6][6] = {"11111", "01111", "00*11", "00001", "00000"};
char now[6][6];
int step;
bool succeed;
int calc(void)
{
	int sum = 0;
	for(int i = 0; i < 5; ++i)
		for(int j = 0; j < 5; ++j) sum += now[i][j] != end[i][j];
	return sum;
}
int dfs(int x, int y, int dep, int last)
{
	int ret = calc();
	if(dep + ret > step) return dep + ret;
	if(!ret) { succeed = true; return dep; }
	int next = INF;
	for(int i = 0; i < 8; ++i)
	{
		if(i + last == 7) continue;
		int xx = x + f[i][0], yy = y + f[i][1];
		if(0 <= xx && xx < 5 && 0 <= yy && yy < 5)
		{
			swap(now[x][y], now[xx][yy]);
			int res = dfs(xx, yy, dep + 1, i);
			if(succeed) return res;
			if(res < next) next = res;
			swap(now[x][y], now[xx][yy]);
		}
	}
	return next;
}
int main()
{
	int t, x, y;
	scanf("%d", &t);
	while(t--)
	{
		for(int i = 0; i < 5; ++i)
		{
			scanf("%s", now[i]);
			for(int j = 0; j < 5; ++j) if(now[i][j] == '*') x = i, y = j;
		}
		succeed = false;
		step = calc();
		while(!succeed && step <= maxstep) step = dfs(x, y, 0, 8);
		if(!succeed) printf("-1\n");
		else printf("%d\n", step);
	}
	return 0;
}

