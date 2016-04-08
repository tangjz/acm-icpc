#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int t, n, x[maxn], y[maxn], e[maxn], tot, que[maxn << 1], fa[maxn << 1];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d", x + i, y + i, e + i);
			que[tot++] = x[i];
			que[tot++] = y[i];
		}
		sort(que, que + tot);
		tot = unique(que, que + tot) - que;
		for(int i = 0; i < n; ++i)
		{
			x[i] = lower_bound(que, que + tot, x[i]) - que;
			y[i] = lower_bound(que, que + tot, y[i]) - que;
		}
		for(int i = 0; i < tot; ++i)
			fa[i] = i;
		for(int i = 0; i < n; ++i)
			if(e[i])
				fa[find(x[i])] = find(y[i]);
		bool flag = 1;
		for(int i = 0; i < n && flag; ++i)
			if(!e[i])
				flag &= find(x[i]) != find(y[i]);
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
