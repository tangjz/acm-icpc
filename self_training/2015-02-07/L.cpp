#include <cstdio>
#include <cstring>
const int maxn = 100001;
int n, m, fa[maxn];
long long dist[maxn];
int find(int x)
{
	if(x == fa[x])
		return x;
	int tmp = fa[x];
	fa[x] = find(fa[x]);
	dist[x] += dist[tmp];
	return fa[x];
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		memset(dist, 0, sizeof dist); 
		for(int i = 1; i <= n; ++i)
			fa[i] = i;
		while(m--)
		{
			int a, b, w, u, v;
			char op[2];
			scanf("%s", op);
			if(op[0] == '!')
			{
				scanf("%d%d%d", &a, &b, &w);
				if((u = find(a)) != (v = find(b)))
				{
					fa[v] = u;
					dist[v] += w + dist[a] - dist[b];
				}
			}
			else
			{
				scanf("%d%d", &a, &b);
				if(find(a) == find(b))
					printf("%d\n", dist[b] - dist[a]);
				else
					puts("UNKNOWN");
			}
		}
	}
	return 0;
}
