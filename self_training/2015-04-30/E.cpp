#include <cstdio>
const int maxn = 233;
int n, k;
long long f[2][maxn][maxn], ans;
int main()
{
	scanf("%d%d", &n, &k);
	for(int t = 0; t <= 1; ++t)
	{
		f[t][0][0] = 1;
		for(int i = 1; i <= n - t; ++i)
			for(int j = 0; j <= (i - 1 | 1) + t; ++j)
				f[t][i][j] = f[t][i - 1][j] + f[t][i - 1][j - 1] * ((i - 1 | 1) + t - j + 1);
	}
	for(int i = 0; i <= k; ++i)
		ans += f[0][n][i] * f[1][n - 1][k - i];
	printf("%lld\n", ans);
	return 0;
}
/*
0: n-0 : (i-1|1)+0
1: n-1 : (i-1|1)+1
*/
