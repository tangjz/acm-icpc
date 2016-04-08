/*
ID: tangjin2
LANG: C++
TASK: concom
*/
#include <cstdio>
#include <cstring>
const int maxn = 101;
int n, p[maxn][maxn], f[maxn];
bool vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	for(int i = 1; i < maxn; ++i)
		if(p[u][i])
		{
			f[i] += p[u][i];
			if(!vis[i] && f[i] > 50)
				dfs(i);
		}
}
int main()
{
	freopen("concom.in", "r", stdin);
	freopen("concom.out", "w", stdout);
	scanf("%d", &n);
	while(n--)
	{
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		p[x][y] += w;
	}
	for(int i = 1; i < maxn; ++i)
	{
		memset(f, 0, sizeof f);
		memset(vis, 0, sizeof vis);
		dfs(i);
		for(int j = 1; j < maxn; ++j)
			if(i != j && f[j] > 50)
				printf("%d %d\n", i, j);
	}
	return 0;
}
