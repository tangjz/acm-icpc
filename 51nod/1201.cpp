#include <cstdio>
const int maxn = 50001, maxs = 316, mod = 1000000007;
int n, m, f[maxs][maxn], ans;
void upd(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int main()
{
	scanf("%d", &n);
	for(m = 1; m * (m + 1) >> 1 <= n; ++m); --m;
	f[1][1] = 1;
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= n; ++j)
		{
			if(i + j <= n)
				upd(f[i][i + j], f[i][j]);
			if(i + 1 <= m && i + j + 1 <= n)
				upd(f[i + 1][i + j + 1], f[i][j]);
		}
	for(int i = 1; i <= m; ++i)
		upd(ans, f[i][n]);
	printf("%d\n", ans);
	return 0;
}
