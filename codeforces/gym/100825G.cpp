#include <cstdio>
#include <cstring>
const int maxn = 25, maxm = 3, maxs = 1 << maxm;
int n, m, pre = 1, cur;
long long f[2][maxs];
bool ban[maxn][maxm];
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(ban, 0, n * maxm * sizeof(bool));
		while(m--)
		{
			double x, y;
			scanf("%lf%lf", &x, &y);
			ban[(int)x][(int)y] = 1;
		}
		memset(f[cur], 0, sizeof f[cur]);
		f[cur][maxs - 1] = 1;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < maxm; ++j)
			{
				pre ^= 1;
				cur ^= 1;
				memset(f[cur], 0, sizeof f[cur]);
				if(!ban[i][j])
					for(int k = 0; k < maxs; ++k)
					{
						if(k & (1 << maxm - 1))
							f[cur][(k << 1) & (maxs - 1)] += f[pre][k];
						f[cur][(k << 1 | 1) & (maxs - 1)] += f[pre][k];
						if(j && (k & (1 << maxm - 1)) && (~k & 1))
							f[cur][(k << 1 | 3) & (maxs - 1)] += f[pre][k];
					}
				else
					for(int k = 0; k < maxs; ++k)
						if(k & (1 << maxm - 1))
							f[cur][(k << 1 | 1) & (maxs - 1)] += f[pre][k];
			}
		printf("%lld\n", f[cur][maxs - 1]);
	}
	return 0;
}
