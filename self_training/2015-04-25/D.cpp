#include <cstdio>
#include <cstring>
const int maxn = 2000010, maxm = 2000010;
int t, n, m, fa[maxn], l[maxn], r[maxn], p[maxn], ans[maxn];
int top, stack[maxn];
int find(int x)
{
	if(x == fa[x])
		return x;
	int tmp = fa[x];
	top = 0;
	stack[top++] = x;
	while(tmp != fa[tmp])
	{
		stack[top++] = tmp;
		tmp = fa[tmp];
	}
	for(int i = 0; i < top; ++i)
		fa[stack[i]] = tmp;
	return tmp;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(ans, 0, sizeof ans);
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++i)
			scanf("%d%d%d", l + i, r + i, p + i);
		for(int i = 1; i <= n + 1; ++i)
			fa[i] = i;
		for(int i = m - 1; i >= 0; --i)
		{
			for(int j = find(l[i]); j <= r[i]; j = find(j))
			{
				ans[j] = p[i];
				fa[j] = find(j + 1);
			}
		}
		for(int i = 1; i <= n; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
