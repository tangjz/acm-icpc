/*
 * 前三种操作模拟即可 最后一种操作记忆化搜索即可 
 */
#include <cstdio>
const int d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int n, m, num[701][701], f[701][701], vis[701][701];
bool flag[701][701];
inline void update(int &x, const int y) { if(x < y) x = y; }
int dp(int x, int y)
{
	if(vis[x][y] == m) return f[x][y];
	f[x][y] = 1, vis[x][y] = m;
	for(int i = 0; i < 4; ++i)
	{
		int xx = x + d[i][0], yy = y + d[i][1];
		if(!flag[xx][yy] && num[xx][yy] < num[x][y]) update(f[x][y], dp(xx, yy) + 1);
	}
	return f[x][y];
}
int main()
{
	int i, j, a, b, c, d, ans;
	char ch[2];
	scanf("%d", &n);
	for(i = 0; i <= n + 1; ++i) flag[0][i] = flag[n + 1][i] = 1;
	for(i = 1; i <= n; ++i) flag[i][0] = flag[i][n + 1] = 1;
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= n; ++j) scanf("%d", &num[i][j]);
	scanf("%d", &m);
	for( ; m; --m)
	{
		scanf("%s", ch);
		if(ch[0] == 'C') { scanf("%d%d%d", &a, &b, &c); num[a][b] = c; }
		else if(ch[0] == 'S')
		{
			scanf("%d%d%d%d",  &a, &b, &c, &d);
			for(i = a; i <= c; ++i)
				for(j = b; j <= d; ++j) flag[i][j] = 1;
		}
		else if(ch[0] == 'B')
		{
			scanf("%d%d%d%d",  &a, &b, &c, &d);
			for(i = a; i <= c; ++i)
				for(j = b; j <= d; ++j) flag[i][j] = 0;
		}
		else
		{
			ans = 0;
			for(i = 1; i <= n; ++i)
				for(j = 1; j <= n; ++j) if(!flag[i][j]) update(ans, dp(i, j));
			printf("%d\n", ans);
		}
	}
	return 0;
}
