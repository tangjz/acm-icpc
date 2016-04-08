#include <cstdio>
#include <cstring>
const int maxn = 2010;
int n, m, s[maxn][maxn], h[maxn][maxn], top, no[maxn], len[maxn], ans1, ans2;
void upd(int x, int y)
{
	if(x < y && ans1 < x * x)
		ans1 = x * x;
	else if(x > y && ans1 < y * y)
		ans1 = y * y;
	if(ans2 < x * y)
		ans2 = x * y;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		s[i][0] = s[i][m + 1] = -1;
		for(int j = 1; j <= m; ++j)
		{
			scanf("%d", &s[i][j]);
			s[i][j] ^= (i & 1) ^ (j & 1);
		}
	}
	for(int j = 1; j <= m; ++j)
		for(int i = 1; i <= n; ++i)
			h[i][j] = s[i][j] == s[i - 1][j] ? h[i - 1][j] + 1 : 1;
	for(int i = 1; i <= n; ++i)
	{
		top = 0;
		for(int j = 1; j <= m + 1; ++j)
		{
			if(s[i][j] != s[i][j - 1])
				for(int tmp = 0; top; --top)
				{
					tmp += len[top];
					upd(h[i][no[top]], tmp);
				}
			int tmp = 0;
			for( ; top && h[i][no[top]] >= h[i][j]; --top)
			{
				tmp += len[top];
				upd(h[i][no[top]], tmp);
			}
			no[++top] = j;
			len[top] = tmp + 1;
		}
	}
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}
