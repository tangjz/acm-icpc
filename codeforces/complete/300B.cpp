#include <cstdio>
int n, m, f[50], c[50][5], vis[50], cnt[3];
int find(int x)
{
	return x == f[x] ? x : f[x] = find(f[x]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		f[i] = i;
	for(int i = 0, u, v; i < m; ++i)
	{
		scanf("%d%d", &u, &v);
		f[find(u)] = find(v);
	}
	for(int i = 1; i <= n; ++i)
	{
		c[find(i)][++c[find(i)][0]] = i;
		if(c[find(i)][0] > 3)
		{
			puts("-1");
			return 0;
		}
	}
	for(int i = 1; i <= n; ++i)
		if(i == f[i])
			++cnt[c[i][0]];
	if(cnt[1] < cnt[2])
	{
		puts("-1");
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		if(c[i][0] == 3)
		{
			printf("%d %d %d\n", c[i][1], c[i][2], c[i][3]);
			vis[c[i][1]] = vis[c[i][2]] = vis[c[i][3]] = 1;
		}
		else if(c[i][0] == 2)
			for(int j = 1; j <= n; ++j)
				if(j == f[j] && !vis[j] && c[j][0] == 1)
				{
					printf("%d %d %d\n", c[i][1], c[i][2], c[j][1]);
					vis[c[i][1]] = vis[c[i][2]] = vis[c[j][1]] = 1;
					break;
				}
	for(int i = 1, t = 0; i <= n; ++i)
		if(!vis[i])
		{
			printf("%d ", i);
			++t;
			if(t % 3 == 0)
				putchar('\n');
		}
	return 0;
}
