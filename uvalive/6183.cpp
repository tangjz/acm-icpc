#include <cstdio>
#include <algorithm>
const int maxn = 11, maxs = 100, maxm = 20 * 20 * 20, INF = 0x3f3f3f3f;
const char *buf = "(){}[]";
int n, m, mat[maxn][4], r, cnt[4], tot, val[maxm][3];
char str[maxs];
int main()
{
	while(scanf("%d%d\n", &n, &m) == 2 && n + m)
	{
		for(int i = 0; i < 3; ++i)
			cnt[i] = 0;
		for(int i = 0, j, k; i < n; ++i)
		{
			for(j = 0; j < 3; ++j)
				mat[i][j] = cnt[j];
			gets(str);
			for(j = 0; str[j] == '.'; ++j);
			mat[i][3] = j;
			for( ; str[j]; ++j)
				for(k = 0; buf[k]; ++k)
					if(str[j] == buf[k])
					{
						cnt[k >> 1] += k & 1 ? -1 : 1;
						break;
					}
		}
		tot = 0;
		for(int i = 1; i <= 20; ++i)
			for(int j = 1; j <= 20; ++j)
				for(int k = 1; k <= 20; ++k)
				{
					int tmp[3] = {i, j, k};
					bool flag = 1;
					for(int x = 0; x < n && flag; ++x)
					{
						int temp = 0;
						for(int y = 0; y < 3; ++y)
							temp += tmp[y] * mat[x][y];
						flag &= temp == mat[x][3];
					}
					if(flag)
					{
						val[tot][0] = i;
						val[tot][1] = j;
						val[tot][2] = k;
						++tot;
					}
				}
		for(int i = 0; i < 3; ++i)
			cnt[i] = 0;
		for(int i = 0; i < m; ++i)
		{
			int out = INF;
			for(int j = 0; j < tot; ++j)
			{
				int tmp = 0;
				for(int k = 0; k < 3; ++k)
					tmp += val[j][k] * cnt[k];
				if(out == INF)
					out = tmp;
				else if(out != tmp)
					out = -1;
			}
			printf("%d%c", out == INF ? -1 : out, " \n"[i == m - 1]);
			gets(str);
			for(int j = 0; str[j]; ++j)
				for(int k = 0; buf[k]; ++k)
					if(str[j] == buf[k])
					{
						cnt[k >> 1] += k & 1 ? -1 : 1;
						break;
					}
		}
	}
	return 0;
}
