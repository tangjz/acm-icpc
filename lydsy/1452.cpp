#include <cstdio>
const int maxn = 300, maxc = 100;
int n, m, a[maxn][maxn], bit[maxc][maxn][maxn];
void add(int b[maxn][maxn], int x, int y, int v)
{
	for(int i; x < n; x += ~x & x + 1)
		for(i = y; i < m; i += ~i & i + 1)
			b[x][i] += v;
}
int sum(int b[maxn][maxn], int x, int y)
{
	int ret = 0;
	for(int i; x >= 0; x -= ~x & x + 1)
		for(i = y; i >= 0; i -= ~i & i + 1)
			ret += b[x][i];
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0, j; i < n; ++i)
		for(j = 0; j < m; ++j)
		{
			scanf("%d", &a[i][j]);
			add(bit[--a[i][j]], i, j, 1);
		}
	int q, typ, x1, y1, x2, y2, c, ans;
	scanf("%d", &q);
	while(q--)
	{
		scanf("%d", &typ);
		if(typ == 1)
		{
			scanf("%d%d%d", &x1, &y1, &c);
			--x1, --y1, --c;
			add(bit[a[x1][y1]], x1, y1, -1);
			a[x1][y1] = c;
			add(bit[a[x1][y1]], x1, y1, 1);
		}
		else
		{
			scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &c);
			x1 -= 2, --x2, y1 -= 2, --y2, --c;
			ans = sum(bit[c], x2, y2) - sum(bit[c], x1, y2) - sum(bit[c], x2, y1) + sum(bit[c], x1, y1);
			printf("%d\n", ans);
		}
	}
	return 0;
}
