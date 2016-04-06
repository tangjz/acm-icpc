#include <cstdio>
#include <cstring>
const int maxn = 1010, maxl = 200;
int t, n, cnt[maxn], sta[maxn][maxl], end[maxn][maxl], maxlen[maxl];
char str[maxn][maxl];
int max(int x, int y)
{
	return x < y ? y : x;
}
int main()
{
	scanf("%d\n", &t);
	while(t--)
	{
		memset(cnt, 0, sizeof cnt);
		memset(maxlen, 0, sizeof maxlen);
		for(n = 0; gets(str[n]) != NULL; ++n)
			if(str[n][0] == '@' && str[n][1] == '\0')
				break;
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0, k = 0; str[i][j]; j = k)
			{
				while(str[i][j] == ' ')
					++j;
				k = j;
				while(str[i][k] && str[i][k] != ' ')
					++k;
				if(j < k)
				{
					sta[i][cnt[i]] = j;
					end[i][cnt[i]] = k;
					maxlen[cnt[i]] = max(maxlen[cnt[i]], k - j);
					++cnt[i];
				}
			}
		}
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < cnt[i]; ++j)
			{
				if(j)
					putchar(' ');
				str[i][end[i][j]] = '\0';
				if(j + 1 == cnt[i])
					printf("%s", str[i] + sta[i][j]);
				else
					printf("%-*s", maxlen[j], str[i] + sta[i][j]);
			}
			putchar('\n');
		}
	}
	return 0;
}
