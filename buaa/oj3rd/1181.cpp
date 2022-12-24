#include <cstdio>
#include <cstring>
const int maxn = 10010;
int n, s, pos[10][maxn], now[10];
char str[maxn], ans[maxn];
int main()
{
	while(scanf("%d%d%s", &n, &s, str) == 3)
	{
		for(int i = 0; i < 10; ++i)
		{
			pos[i][0] = 0;
			now[i] = 1;
		}
		for(int i = 0, j; i < n; ++i)
		{
			j = str[i] - '0';
			pos[j][++pos[j][0]] = i;
		}
		for(int i = 0, j; i < n - s; ++i)
		{
			for(int k = i == 0; k < 10; ++k)
				if(now[k] <= pos[k][0] && pos[k][now[k]] <= i + s)
				{
					j = k;
					break;
				}
			ans[i] = '0' + j;
			for(int k = 0; k < 10; ++k)
				while(now[k] <= pos[k][0] && pos[k][now[k]] < pos[j][now[j]])
					++now[k];
			++now[j];
		}
		ans[n - s] = '\0';
		puts(ans);
	}
	return 0;
}
