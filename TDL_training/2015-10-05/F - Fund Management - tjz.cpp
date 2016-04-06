#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxm = 110, maxn = 10, maxs = 233333, maxl = 15;
int m, n, limit, tot, lim[maxn], sz[maxs], p[maxm][maxs];
double fir;
LL w[maxn][maxm], f[maxm][maxs], que[maxs];
char str[maxn][maxl];
void dfs(int dep, int cnt, LL mask)
{
	if(dep == n)
	{
		que[tot++] = mask;
		return;
	}
	for(int i = 0; i <= lim[dep] && cnt + i <= limit; ++i)
		dfs(dep + 1, cnt + i, mask | ((LL)i << (4 * dep)));
}
void print(int date, int idx)
{
	if(date > 1)
		print(date - 1, p[date][idx]);
	if(p[date][idx] == idx)
	{
		puts("HOLD");
		return;
	}
	LL &last = que[p[date][idx]], &cur = que[idx];
	for(int i = 0; i < n; ++i)
		if(((last >> (4LL * i)) & 15) != ((cur >> (4LL * i)) & 15))
		{
			if(((last >> (4LL * i)) & 15) + 1 == ((cur >> (4LL * i)) & 15))
				printf("BUY %s\n", str[i]);
			else
				printf("SELL %s\n", str[i]);
			break;
		}
}
int main()
{
	while(scanf("%lf%d%d%d", &fir, &m, &n, &limit) == 4)
	{
		for(int i = 0; i < n; ++i)
		{
			int cc;
			double ww;
			scanf("%s%d%d", str[i], &cc, lim + i);
			for(int j = 1; j <= m; ++j)
			{
				scanf("%lf", &ww);
				w[i][j] = (LL)(ww * 100 + 0.01);
				w[i][j] *= cc;
			}
		}
		tot = 0;
		dfs(0, 0, 0);
		sort(que, que + tot);
		for(int i = 0; i < tot; ++i)
		{
			sz[i] = 0;
			//printf("%d : %d\n", i, que[i]);
			for(int j = 0; j < n; ++j)
			{
				sz[i] += (que[i] >> (4LL * j)) & 15;
				//printf("%d%c", (que[i] >> (4LL * j)) & 15, " \n"[j == n - 1]);
			}
		}
		for(int i = 0; i <= m; ++i)
			for(int j = 0; j < tot; ++j)
				f[i][j] = -1;
		f[0][0] = (LL)(fir * 100 + 0.01);
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < tot; ++j)
			{
				if(f[i][j] == -1)
					continue;
				LL &cur = que[j];
				if(f[i + 1][j] < f[i][j])
				{
					f[i + 1][j] = f[i][j];
					p[i + 1][j] = j;
					//printf("HOLD %d %d -> %d %d : %.2f\n", i, j, i + 1, j, f[i + 1][j]);
				}
				if(sz[j] < limit)
				{
					for(int k = 0; k < n; ++k)
					{
						int now = (cur >> (4LL * k)) & 15;
						if(now < lim[k] && f[i][j] >= w[k][i + 1])
						{
							LL nxt = cur + (1LL << (4LL * k));
							int jj = lower_bound(que, que + tot, nxt) - que;
							if(f[i + 1][jj] < f[i][j] - w[k][i + 1])
							{
								f[i + 1][jj] = f[i][j] - w[k][i + 1];
								p[i + 1][jj] = j;
								//printf("BUY %d %d -> %d %d : %.2f\n", i, j, i + 1, jj, f[i + 1][jj]);
							}
						}
					}
				}
				if(sz[j] > 0)
				{
					for(int k = 0; k < n; ++k)
					{
						int now = (cur >> (4LL * k)) & 15;
						if(now > 0)
						{
							LL nxt = cur - (1LL << (4LL * k));
							int jj = lower_bound(que, que + tot, nxt) - que;
							if(f[i + 1][jj] < f[i][j] + w[k][i + 1])
							{
								f[i + 1][jj] = f[i][j] + w[k][i + 1];
								p[i + 1][jj] = j;
								//printf("SELL %d %d -> %d %d : %.2f\n", i, j, i + 1, jj, f[i + 1][jj]);
							}
						}
					}
				}
			}
		printf("%lld.%02d\n", f[m][0] / 100, (int)(f[m][0] % 100));
		print(m, 0);
	}
	return 0;
}
