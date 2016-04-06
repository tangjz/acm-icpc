#include <cstdio>
#include <cstring>
const int maxn = 5002, maxs = 26, INF = 0x3f3f3f3f;
int tt, n, m, pre[2][maxs], suf[2][maxs], f[maxn][maxn];
char s[maxn], t[maxn];
void upd(int &x, int y)
{
	if(x > y)
		x = y;
}
int main()
{
	scanf("%d", &tt);
	while(tt--)
	{
		scanf("%s%s", s + 1, t + 1);
		n = strlen(s + 1);
		m = strlen(t + 1);
		memset(pre, 0x3f, sizeof pre);
		memset(suf, -1, sizeof suf);
		for(int i = 1; i <= n; ++i)
		{
			if(pre[0][s[i] - 'A'] == INF)
				pre[0][s[i] - 'A'] = i;
			suf[0][s[i] - 'A'] = i;
		}
		for(int i = 1; i <= m; ++i)
		{
			if(pre[1][t[i] - 'A'] == INF)
				pre[1][t[i] - 'A'] = i;
			suf[1][t[i] - 'A'] = i;
		}
		for(int i = 0; i <= n; ++i)
			for(int j = 0; j <= m; ++j)
			{
				f[i][j] = !i && !j ? 0 : INF;
				if(i)
				{
					int cnt = 0;
					for(int k = 0; k < maxs; ++k)
						if((pre[0][k] < i || pre[1][k] <= j) && (i <= suf[0][k] || j < suf[1][k]))
							++cnt;
					upd(f[i][j], f[i - 1][j] + cnt);
				}
				if(j)
				{
					int cnt = 0;
					for(int k = 0; k < maxs; ++k)
						if((pre[0][k] <= i || pre[1][k] < j) && (i < suf[0][k] || j <= suf[1][k]))
							++cnt;
					upd(f[i][j], f[i][j - 1] + cnt);
				}
			}
		printf("%d\n", f[n][m]);
	}
	return 0;
}
