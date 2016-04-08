#include <cstdio>
#include <cstring>
int n, cnt[1001], sta[1001][181], end[1001][181], maxlen[181];
char str[1001][181];
int max(int x, int y)
{
	return x < y ? y : x;
}
int main()
{
	while(gets(str[n]) != NULL)
		++n;
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
			printf("%-*s", maxlen[j], str[i] + sta[i][j]);
		}
		putchar('\n');
	}
	return 0;
}