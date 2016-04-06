#include <cstdio>
int h, w, k, cnt, hor[1010][1010], ver[1010][1010], ans[1010][1010];
char str[1010];
int main()
{
	scanf("%d%d%d", &h, &w, &k);
	for(int i = 0; i < 2 * h - 1; ++i)
	{
		scanf("%s", str);
		if(i & 1)
		{
			for(int j = 0; j < w; ++j)
				if(str[j] == 'N')
				{
					ver[i >> 1][j] = 1;
					++cnt;
				}
		}
		else
		{
			for(int j = 0; j < w - 1; ++j)
				if(str[j] == 'N')
				{
					hor[i >> 1][j] = 1;
					++cnt;
				}
		}
	}
	if(k == 1)
	{
		if(cnt * 4 > h * (w - 1) + (h - 1) * w)
			puts("NO");
		else
		{
			puts("YES");
			for(int i = 0; i < h; ++i, putchar('\n'))
				for(int j = 0; j < w; ++j)
					printf("1 ");
		}
		return 0;
	}
	if(h <= w)
	{
		ans[0][0] = 0;
		for(int i = 1; i < w; ++i)
			ans[0][i] = ans[0][i - 1] ^ hor[0][i - 1];
		for(int i = 1; i < h; ++i)
		{
			ans[i][0] = 0;
			cnt = ans[i - 1][0] ^ ans[i][0] ^ ver[i - 1][0];
			for(int j = 1; j < w; ++j)
			{
				ans[i][j] = ans[i][j - 1] ^ hor[i][j - 1];
				cnt += ans[i - 1][j] ^ ans[i][j] ^ ver[i - 1][j];
			}
			if(cnt * 2 > w)
			{
				for(int j = 0; j < w; ++j)
					ans[i][j] ^= 1;
			}
		}
	}
	else
	{
		ans[0][0] = 0;
		for(int i = 1; i < h; ++i)
			ans[i][0] = ans[i - 1][0] ^ ver[i - 1][0];
		for(int i = 1; i < w; ++i)
		{
			ans[0][i] = 0;
			cnt = ans[0][i - 1] ^ ans[0][i] ^ hor[0][i - 1];
			for(int j = 1; j < h; ++j)
			{
				ans[j][i] = ans[j - 1][i] ^ ver[j - 1][i];
				cnt += ans[j][i - 1] ^ ans[j][i] ^ hor[j][i - 1];
			}
			if(cnt * 2 > h)
			{
				for(int j = 0; j < h; ++j)
					ans[j][i] ^= 1;
			}
		}
	}
	puts("YES");
	for(int i = 0; i < h; ++i, putchar('\n'))
		for(int j = 0; j < w; ++j)
			printf("%d ", ans[i][j] + 1);
	return 0;
}
