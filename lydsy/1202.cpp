#include <cstdio>
const int maxn = 101;
int t, n, m, fa[maxn], dis[maxn];
bool flag;
int find(int x)
{
	if(x == fa[x])
		return x;
	int t = fa[x];
	fa[x] = find(fa[x]);
	dis[x] += dis[t];
	return fa[x];
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		flag = 1;
		scanf("%d%d", &n, &m);
		for(int i = 0; i <= n; ++i)
		{
			fa[i] = i;
			dis[i] = 0;
		}
		while(m--)
		{
			int l, r, w;
			scanf("%d%d%d", &l, &r, &w);
			if(!flag)
				continue;
			--l;
			if(find(l) != find(r))
			{
				int u = find(l), v = find(r);
				fa[u] = v;
				dis[u] = dis[r] - dis[l] + w;
			}
			else if(dis[l] - dis[r] != w)
				flag = 0;
		}
		puts(flag ? "true" : "false");
	}
	return 0;
}
