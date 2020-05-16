#include <stdio.h>
#include <cstring>
const int maxn = 41;
int n, m, match[maxn][maxn], ans;
char str[maxn][maxn], buf[maxn][maxn];
void dfs(int, int);
inline void chk(int x, int y)
{
	if(x < 0 || x >= n || y < 0 || y >= m)
		return;
	if(str[x][y] == 'L')
		dfs(x, y);
	else
		str[x][y] = 'W';
}
void dfs(int x, int y)
{
	str[x][y] = 'W';
	chk(x - 1, y);
	chk(x, y - 1);
	chk(x + 1, y);
	chk(x, y + 1);
}
bool path(int, int);
inline bool test(int x, int y)
{
	if(x < 0 || x >= n || y < 0 || y >= m)
		return 0;
	if(buf[x][y] == 'C')
	{
		buf[x][y] = 'W';
		int idx = match[x][y];
		if(idx == -1 || path(idx / m, idx % m))
			return 1;
	}
	return 0;
}
bool path(int x, int y)
{
	int idx = x * m + y;
	if(test(x - 1, y))
	{
		match[x - 1][y] = idx;
		return 1;
	}
	if(test(x, y - 1))
	{
		match[x][y - 1] = idx;
		return 1;
	}
	if(test(x + 1, y))
	{
		match[x + 1][y] = idx;
		return 1;
	}
	if(test(x, y + 1))
	{
		match[x][y + 1] = idx;
		return 1;
	}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", str[i]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(str[i][j] == 'L')
			{
				++ans;
				dfs(i, j);
			}
	memset(match, -1, sizeof match);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(str[i][j] == 'C')
			{
				++ans;
				if((i & 1) == (j & 1))
				{
					memcpy(buf, str, sizeof str);
					if(path(i, j))
						--ans;
				}
			}
	printf("%d\n", ans);
	return 0;
}
