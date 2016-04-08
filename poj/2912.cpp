#include <cstdio>
const int maxn = 501, maxm = 2001;
int n, m, fa[maxn * 3], query[maxm][3], id, pos, cnt;
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		id = pos = cnt = 0;
		for(int i = 1; i <= m; ++i)
		{
			int x, y;
			char op;
			scanf("%d%c%d", &x, &op, &y);
			if(op == '=')
			{
				query[i][0] = 1;
				query[i][1] = x + 1;
				query[i][2] = y + 1;
			}
			else if(op == '<')
			{
				query[i][0] = 2;
				query[i][1] = y + 1;
				query[i][2] = x + 1;
			}
			else
			{
				query[i][0] = 2;
				query[i][1] = x + 1;
				query[i][2] = y + 1;
			}
		}
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= n * 3; ++j)
				fa[j] = j;
			bool flag = 0;
			for(int j = 1; j <= m; ++j)
			{
				int &d = query[j][0], &x = query[j][1], &y = query[j][2];
				if(x == i || y == i)
					continue;
				int fx1 = find(x), fx2 = find(x + n), fx3 = find(x + n + n);
				int fy1 = find(y), fy2 = find(y + n), fy3 = find(y + n + n);
				if(d == 1)
				{
					if(fx1 == fy2 || fx1 == fy3 || fy1 == fx2 || fy1 == fx3)
					{
						flag = 1;
						if(pos < j)
							pos = j;
						break;
					}
					fa[find(fx1)] = find(fy1);
					fa[find(fx2)] = find(fy2);
					fa[find(fx3)] = find(fy3);
				}
				else
				{
					if(fx1 == fy1 || fx1 == fy3 || fx2 == fy1)
					{
						flag = 1;
						if(pos < j)
							pos = j;
						break;
					}
					fa[find(fx1)] = find(fy2);
					fa[find(fx2)] = find(fy3);
					fa[find(fx3)] = find(fy1);
				}
			}
			if(!flag)
			{
				id = i;
				++cnt;
				if(cnt > 1)
					break;
			}
		}
		if(!cnt)
			puts("Impossible");
		else if(cnt == 1)
			printf("Player %d can be determined to be the judge after %d lines\n", id - 1, pos);
		else
			puts("Can not determine");
	}
	return 0;
}