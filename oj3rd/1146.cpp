#include <cstdio>
const int maxn = 21;
int n, m, a[maxn], p[maxn];
bool vis[maxn];
void dfs(int dep)
{
	if(dep == m)
	{
		for(int i = 0; i < m; ++i)
			printf("%d%c", a[p[i]], " \n"[i == m - 1]);
		return;
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
		{
			p[dep] = i;
			vis[i] = 1;
			dfs(dep + 1);
			vis[i] = 0;
		}
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		dfs(0);
	}
	return 0;
}
