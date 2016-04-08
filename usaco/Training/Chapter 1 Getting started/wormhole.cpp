/*
ID: tangjin2
LANG: C++
TASK: wormhole
*/
#include <cstdio>
const int maxn = 13;
int n, x[maxn], y[maxn], nxt[maxn], pos[maxn], ans;
void dfs(int dep)
{
	if(dep == (n >> 1))
	{
		bool flag = 1;
		for(int i = 1; i <= n && flag; ++i)
		{
			bool vis[maxn] = {};
			for(int j = i; nxt[j] && flag; j = pos[nxt[j]])
			{
				flag &= !vis[j];
				vis[j] = 1;
			}
		}
		if(!flag)
			++ans;
		return;
	}
	for(int i = 1; i <= n; ++i)
		if(!pos[i])
		{
			for(int j = i + 1; j <= n; ++j)
				if(!pos[j])
				{
					pos[i] = j;
					pos[j] = i;
					dfs(dep + 1);
					pos[j] = 0;
				}
			pos[i] = 0;
			break;
		}
}
int main()
{
	freopen("wormhole.in", "r", stdin);
	freopen("wormhole.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", x + i, y + i);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(x[i] < x[j] && y[i] == y[j] && (!nxt[i] || x[j] < x[nxt[i]]))
				nxt[i] = j;
	dfs(0);
	printf("%d\n", ans);
	return 0;
}
