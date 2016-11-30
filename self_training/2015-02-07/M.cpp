#include <cmath>
#include <cstdio>
const int maxn = 201, maxm = 50010, maxq = 50010, maxc = 10;
int n, m, q, fa[maxn][maxm], ans[maxc];
struct Query
{
	char op;
	int x, y, r, c, l;
} query[maxq];
int min(int x, int y)
{
	return x < y ? x : y;
}
int max(int x, int y)
{
	return x < y ? y : x;
}
int abs(int x)
{
	return x < 0 ? -x : x;
}
int find(int x, int y)
{
	return y == fa[x][y] ? y : fa[x][y] = find(x, fa[x][y]);
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &q) == 3)
	{
		for(int i = 1; i < maxc; ++i)
			ans[i] = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j <= m; ++j)
				fa[i][j] = j;
		for(int i = 0; i < q; ++i)
		{
			char op[10];
			int x, y, c, r, l = 0;
			scanf("%s%d%d%d%d", op, &x, &y, &r, &c);
			if(op[0] == 'R')
				scanf("%d", &l);
			query[i] = (Query){op[0], x, y, r, c, l};
		}
		for(int t = q - 1; t >= 0; --t)
		{
			char &op = query[t].op;
			int &x = query[t].x, &y = query[t].y, &r = query[t].r, &c = query[t].c, &l = query[t].l;
			switch(op)
			{
				case 'C' :
					for(int i = max(x - r, 0), ii = min(x + r, n - 1); i <= ii; ++i)
						for(int j = find(i, max(y - (int)sqrt(r * r - (i - x) * (i - x)), 0)), jj = min(y + (int)sqrt(r * r - (i - x) * (i - x)), m - 1); j <= jj; j = find(i, j))
						{
							++ans[c];
							fa[i][j] = j + 1;
						}
					break;
				case 'D' :
					for(int i = max(x - r, 0), ii = min(x + r, n - 1); i <= ii; ++i)
						for(int j = find(i, max(y - (r - abs(x - i)), 0)), jj = min(y + (r - abs(x - i)), m - 1); j <= jj; j = find(i, j))
						{
							++ans[c];
							fa[i][j] = j + 1;
						}
					break;
				case 'R' :
					for(int i = x, ii = min(x + r - 1, n - 1); i <= ii; ++i)
						for(int j = find(i, y), jj = min(y + c - 1, m - 1); j <= jj; j = find(i, j))
						{
							++ans[l];
							fa[i][j] = j + 1;
						}
					break;
				case 'T' :
					for(int i = x, ii = min(x + (r - 1 >> 1), n - 1); i <= ii; ++i)
						for(int j = find(i, max(y - ((r - 1 >> 1) - (i - x)), 0)), jj = min(y + ((r - 1 >> 1) - (i - x)), m - 1); j <= jj; j = find(i, j))
						{
							++ans[c];
							fa[i][j] = j + 1;
						}
			}
		}
		for(int i = 1; i < maxc; ++i)
			printf("%d%c", ans[i], " \n"[i + 1 == maxc]);
	}
	return 0;
}
