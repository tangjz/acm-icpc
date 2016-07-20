#include <cstdio>
#include <cstring>
const int maxn = 55, dx[] = {0, 1, -1, 0}, dy[] = {1, 0, 0, -1};
int n, m, match[maxn][maxn], ans, sum[2];
char str[maxn][maxn];
bool vis[maxn][maxn];
bool path(int x, int y)
{
	for(int o = 0; o < 4; ++o)
	{
		if(x + dx[o] < 0 || x + dx[o] >= n
		|| y + dy[o] < 0 || y + dy[o] >= m
		|| vis[x + dx[o]][y + dy[o]]
		|| str[x + dx[o]][y + dy[o]] == 'X')
			continue;
		vis[x + dx[o]][y + dy[o]] = 1;
		if(!match[x + dx[o]][y + dy[o]]
		|| path(match[x + dx[o]][y + dy[o]] / m, match[x + dx[o]][y + dy[o]] % m))
		{
			match[x + dx[o]][y + dy[o]] = x * m + y;
			return 1;
		}
	}
	return 0;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		ans = sum[0] = sum[1] = 0;
		for(int i = 0; i < n; ++i)
			scanf("%s", str[i]);
		memset(match, 0, sizeof match);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
			{
				if(str[i][j] == 'X')
					continue;
				++sum[(i + j) & 1];
				if(~(i + j) & 1)
					continue;
				memset(vis, 0, sizeof vis);
				if(path(i, j))
					++ans;
			}
		puts(ans < (sum[0] < sum[1] ? sum[1] : sum[0]) ? "1" : "2");
	}
	return 0;
}
