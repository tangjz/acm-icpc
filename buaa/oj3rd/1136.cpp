#include <cstdio>
#include <cstring>
const int maxn = 11, maxv = 27;
int n, cnt;
double f[maxn][maxv], p1, p2;
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		cnt = 0;
		p1 = p2 = 0;
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for(int i = 1; i <= n; ++i)
		{
			int c, p;
			scanf("%d%d", &c, &p);
			if(p)
				cnt += c;
			for(int j = 0; j < maxv; ++j)
			{
				if(j + c >= maxv)
				{
					p1 += p / 100.0 * f[i - 1][j] * i;
					p2 += p / 100.0 * f[i - 1][j];
				}
				else
					f[i][j + c] += p / 100.0 * f[i - 1][j];
				f[i][j] += (100 - p) / 100.0 * f[i - 1][j];
			}
		}
		if(cnt < maxv)
			puts("-1");
		else
			printf("%.4f\n", p1 / p2);
	}
	return 0;
}
