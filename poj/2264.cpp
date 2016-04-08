#include <cstdio>
#include <cstring>
const int maxs = 101;
int slen, tlen, f[maxs][maxs], pre[maxs][maxs], len, pos[maxs][2];
char s[maxs], t[maxs];
int main()
{
	while(scanf("%s%s", s, t) == 2)
	{
		memset(f, 0, sizeof f);
		slen = strlen(s);
		tlen = strlen(t);
		for(int i = 1; i <= slen; ++i)
			for(int j = 1; j <= tlen; ++j)
				if(s[i - 1] == t[j - 1])
				{
					f[i][j] = f[i - 1][j - 1] + 1;
					pre[i][j] = i * maxs + j;
				}
				else if(f[i - 1][j] < f[i][j - 1])
				{
					f[i][j] = f[i][j - 1];
					pre[i][j] = pre[i][j - 1];
				}
				else
				{
					f[i][j] = f[i - 1][j];
					pre[i][j] = pre[i - 1][j];
				}
		len = f[slen][tlen];
		for(int i = len - 1, tmp = pre[slen][tlen], x, y; i >= 0; --i, tmp = pre[x - 1][y - 1])
		{
			x = tmp / maxs;
			y = tmp % maxs;
			pos[i][0] = x - 1;
			pos[i][1] = y - 1;
		}
		int x = 0, y = 0;
		for(int i = 0; i < len; ++i, ++x, ++y)
		{
			while(x < pos[i][0])
				putchar(s[x++]);
			while(y < pos[i][1])
				putchar(t[y++]);
			putchar(s[x]);
		}
		while(s[x])
			putchar(s[x++]);
		while(t[y])
			putchar(t[y++]);
		putchar('\n');
	}
	return 0;
}