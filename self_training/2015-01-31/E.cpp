#include <cstdio>
const int maxn = 1000086;
int n, fa[maxn], ans;
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 1; i <= n; ++i)
			fa[i] = i;
		for(int i = 1, x; i <= n; ++i)
		{
			scanf("%d", &x);
			fa[find(i)] = find(x);
		}
		ans = n;
		for(int i = 1; i <= n; ++i)
			if(i == find(i))
				--ans;
		printf("%d\n", ans);
	}
	return 0;
}
