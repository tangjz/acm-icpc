#include <cstdio>
const int maxn = 1e5 + 1;
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
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 0; i <= n; ++i)
		{
			fa[i] = i;
			dist[i] = 0;
		}
		while(m--)
		{
			int s, t, c, u, v;
			scanf("%d%d%d", &s, &t, &c);
			if((u = find(s - 1)) != (v = find(t)))
			{
				fa[v] = u;
				dist[v] = c + dist[s - 1] - dist[t];
				puts("Accepted!");
			}
			else
				puts(dist[t] - dist[s - 1] == c ? "Accepted!" : "Error!");
		}
		for(int i = 1; i <= n; ++i)
			if(find(i - 1) != find(i))
				puts("Unknown!");
			else
				printf("%lld\n", dist[i] - dist[i - 1]);
	}
	return 0;
}
