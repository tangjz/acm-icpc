#include <cstdio>
#include <cstring>
const int maxn = 1001;
int t, n, m, q, fa[maxn << 1], dis[maxn << 1];
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
		scanf("%d%d%d", &n, &m, &q);
		for(int i = 1; i <= n + m; ++i)
		{
			fa[i] = i;
			dis[i] = 0;
		}
		bool flag = 0;
		while(q--)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if(flag)
				continue;
			int fu = find(u), fv = find(n + v);
			if(fu != fv)
			{
				fa[fu] = fv;
				dis[fu] = dis[n + v] - dis[u] + w;
			}
			else if(dis[u] - dis[n + v] != w)
				flag = 1;
		}
		puts(!flag ? "Yes" : "No");
	}
	return 0;
}
