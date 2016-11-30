#include <cstdio>
const int maxn = 1e5 + 1, maxm = 1e5 + 1, maxt = 1e5 + 1;
int n, m, t, fa[maxn], u[maxm], v[maxm], query[maxt][3], ans[maxt];
bool vis[maxm];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d", u + i, v + i);
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i)
	{
		int x, y;
		char op[2];
		scanf("%s", op);
		if(op[0] == 'Q')
		{
			scanf("%d%d", &x, &y);
			query[i][0] = 1;
			query[i][1] = x;
			query[i][2] = y;
		}
		else
		{
			scanf("%d", &x);
			if(vis[x])
				query[i][0] = 2;
			else
			{
				query[i][1] = x;
				vis[x] = 1;
			}
		}
	}
	for(int i = 1; i <= n; ++i)
		fa[i] = i;
	for(int i = 1; i <= m; ++i)
		if(!vis[i])
			fa[find(u[i])] = find(v[i]);
	for(int i = t; i > 0; --i)
		if(query[i][0] == 1)
			ans[i] = find(query[i][1]) == find(query[i][2]);
		else if(!query[i][0])
			fa[find(u[query[i][1]])] = find(v[query[i][1]]);
	for(int i = 1; i <= t; ++i)
		if(query[i][0] == 1)
			printf("%d\n", ans[i]);
	return 0;
}
