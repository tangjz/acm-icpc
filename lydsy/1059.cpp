/*
 * 行或列的相对位置不变，问题转化为求是否有n个不在同一行或同一列的点
 */
#include <cstdio>
#include <cstring>
const int maxn = 201;
int n, mark[maxn];
bool vis[maxn][maxn], y[maxn];
bool find(int x)
{
	for(int i = 1; i <= n; ++i)
		if(vis[x][i] && !y[i])
		{
			y[i] = 1;
			if(!mark[i] || find(mark[i]))
			{
				mark[i] = x;
				return 1;
			}
		}
	return 0;
}
bool check()
{
	for(int i = 1; i <= n; ++i)
	{
		memset(y, 0, sizeof y);
		if(!find(i)) return 0;
	}
	return 1;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		memset(vis, 0, sizeof vis);
		memset(mark, 0, sizeof mark);
		scanf("%d", &n);
		for(int i = 1, x; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
			{
				scanf("%d", &x);
				if(x) vis[i][j] = 1;
			}
		puts(check() ? "Yes" : "No");
	}
	return 0;
}
