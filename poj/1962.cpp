#include <cstdio>
const int maxn = 20001, mod = 1000;
int t, n, fa[maxn], dist[maxn];
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
	int x, y;
	char op[2];
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			fa[i] = i;
			dist[i] = 0;
		}
		while(scanf("%s", op) != EOF && op[0] != 'O')
			if(op[0] == 'E')
			{
				scanf("%d", &x);
				find(x);
				printf("%d\n", dist[x]);
			}
			else
			{
				scanf("%d%d", &x, &y);
				fa[x] = y;
				dist[x] = (x < y ? y - x : x - y) % mod;
			}
	}
	return 0;
}