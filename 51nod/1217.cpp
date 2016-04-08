#include <cstdio>
const int maxn = 5001, maxnn = 12497501, maxa = 1e6 + 1, maxs = 11;
int n, k, a[maxn], lim, diff[maxa], que[maxs][2], xque[maxs * 2], pos[maxn], fa[maxn], tot, cnt, xtot;
struct Node
{
	int nxt;
	short x, y;
} e[maxnn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d", &n, &k);
	int s = k * (k + 1) >> 1;
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		if(lim < a[i])
			lim = a[i];
	}
	++lim;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
		{
			int dist = a[i] < a[j] ? a[j] - a[i] : a[i] - a[j];
			e[++tot] = (Node){diff[dist], i, j};
			diff[dist] = tot;
		}
	for(int m = n - k > 1 ? n - k : 1; m <= lim; ++m)
	{
		tot = 0;
		for(int i = m; i < lim && tot <= s; i += m)
			for(int it = diff[i]; it && tot <= s; it = e[it].nxt)
			{
				que[tot][0] = e[it].x;
				que[tot++][1] = e[it].y;
			}
		if(tot > s)
			continue;
		cnt = xtot = 0;
		for(int i = 0; i < tot; ++i)
		{
			int &x = que[i][0], &y = que[i][1];
			if(pos[x] != m)
			{
				xque[xtot++] = x;
				pos[x] = m;
				fa[x] = x;
			}
			if(pos[y] != m)
			{
				xque[xtot++] = y;
				pos[y] = m;
				fa[y] = y;
			}
			fa[find(x)] = find(y);
		}
		for(int i = 0; i < xtot; ++i)
		{
			int &x = xque[i];
			if(x != find(x))
				++cnt;
		}
		if(cnt <= k)
		{
			printf("%d\n", m);
			break;
		}
	}
	return 0;
}
