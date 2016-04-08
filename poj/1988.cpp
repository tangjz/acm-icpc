#include <cstdio>
const int maxn = 30001;
int p, x, y, fa[maxn], size[maxn], dist[maxn];
char op[2];
int find(int x)
{
	if(x == fa[x])
		return x;
	int t = fa[x];
	fa[x] = find(fa[x]);
	dist[x] += dist[t];
	return fa[x];
}
int main()
{
	while(scanf("%d", &p) == 1)
	{
		for(int i = 1; i < maxn; ++i)
		{
			fa[i] = i;
			size[i] = 1;
			dist[i] = 0;
		}
		while(p--)
		{
			scanf("%s", op);
			if(op[0] == 'M')
			{
				scanf("%d%d", &x, &y);
				x = find(x), y = find(y);
				if(x != y)
				{
					fa[y] = x;
					dist[y] = size[x];
					size[x] += size[y];
				}
			}
			else
			{
				scanf("%d", &x);
				printf("%d\n", size[find(x)] - dist[x] - 1);
			}
		}
	}
	return 0;
}