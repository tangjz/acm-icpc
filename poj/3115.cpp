#include <cstdio>
#include <cstring>
const int maxn = 5001, maxm = 21;
int n, m, x;
long long f[maxn][maxm], ans;
int main()
{
	int e, a;
	while(scanf("%d%d%d%d", &m, &n, &e, &a) == 4 && m + n + e + a)
	{
		memset(f, 0x3f, sizeof f);
		x = e * a;
		f[0][0] = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j < m; ++j)
			{
				scanf("%d%d", &e, &a);
				for(int k = 0; k < m; ++k)
				{
					int tmp = e * a;
					if(j != k)
						tmp += x;
					if(f[i][j] > f[i - 1][k] + tmp)
						f[i][j] = f[i - 1][k] + tmp;
				}
			}
		ans = f[n][0];
		for(int i = 1; i < m; ++i)
			if(ans > f[n][i])
				ans = f[n][i];
		printf("%lld\n", ans);
	}
	return 0;
}