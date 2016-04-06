#include <cstdio>
const int maxn = 1e5 + 1;
int n, m, fa[maxn], u, v, ans;
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 1; i <= n; ++i)
			fa[i] = i;
		while(m--)
		{
			scanf("%d%d", &u, &v);
			fa[find(u)] = find(v);
		}
		ans = -1;
		for(int i = 1; i <= n; ++i)
			if(i == find(i))
				++ans;
		printf("%d\n", ans);
	}
	return 0;
}
