#include <cstdio>
const int maxn = 1001, maxk = 1001, mod = 10000;
int n, k, f[maxn][maxk];
void inc(int &x, int y)
{
	if(y < 0)
		y += mod;
	x += y;
	if(x >= mod)
		x -= mod;
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= k; ++j)
		{
			if(!i && !j)
			{
				f[i][j] = 1;
				continue;
			}
			if(j)
				inc(f[i][j], f[i][j - 1]);
			if(i)
			{
				inc(f[i][j], f[i - 1][j]);
				if(i <= j)
					inc(f[i][j], -f[i - 1][j - i]);
			}
		}
	int ans = f[n][k];
	if(k)
		inc(ans, -f[n][k - 1]);
	printf("%d\n", ans);
	return 0;
}

