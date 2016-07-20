#include <cstdio>
#include <cstring>
const int maxn = 20010, maxq = 5010;
int t, n, q, p[maxn], typ[maxq], x[maxq], y[maxq], fa[maxn], ans[maxq];
bool vis[maxn], used[maxq];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &q);
		for(int i = 1; i <= n; ++i)
			scanf("%d", p + i);
		memset(vis, 0, sizeof vis);
		memset(used, 0, sizeof used);
		for(int i = 1; i <= q; ++i)
		{
			char str[10];
			scanf("%s", str);
			typ[i] = str[0] == 'C';
			if(typ[i] == 1)
			{
				scanf("%d", x + i);
				if(!vis[x[i]])
				{
					used[i] = 1;
					vis[x[i]] = 1;
				}
			}
			else
			{
				scanf("%d%d", x + i, y + i);
				used[i] = 1;
			}
		}
		for(int i = 1; i <= n; ++i)
			fa[i] = i;
		for(int i = 1; i <= n; ++i)
			if(!vis[i] && p[i])
				fa[find(i)] = find(p[i]);
		for(int i = q; i >= 1; --i)
		{
			if(!used[i])
				continue;
			if(!typ[i])
				ans[i] = find(x[i]) == find(y[i]);
			else if(p[x[i]])
				fa[find(x[i])] = find(p[x[i]]);
		}
		printf("Case #%d:\n", Case);
		for(int i = 1; i <= q; ++i)
			if(!typ[i])
				puts(ans[i] ? "YES" : "NO");
	}
	return 0;
}
