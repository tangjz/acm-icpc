#include <cstdio>
#include <cstring>
const int maxn = 555;
int n, m, b, mod, f[maxn][maxn];
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &b, &mod);
	f[0][0] = 1;
	for(int t = 1; t <= n; ++t)
	{
		int x;
		scanf("%d", &x);
		for(int j = 1; j <= m; ++j)
			for(int k = x; k <= b; ++k)
				inc(f[j][k], f[j - 1][k - x]);
	}
	int ans = 0;
	for(int i = 0; i <= b; ++i)
		inc(ans, f[m][i]);
	printf("%d\n", ans);
	return 0;
}
