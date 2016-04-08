#include <cstdio>
#include <cstring>
const int maxn = 1001, mod = 100000007;
int n, s, a, b, f[maxn][maxn], ans;
int main()
{
	scanf("%d%d%d%d", &n, &s, &a, &b);
	f[0][0] = 1;
	for(int i = 1; i < n; ++i)
	{
		memcpy(f[i], f[i - 1], sizeof f[0]);
		for(int j = 0, k = n - i; j < n; ++j, k = k + 1 < n ? k + 1 : 0)
		{
			f[i][j] += f[i - 1][k];
			if(f[i][j] >= mod)
				f[i][j] -= mod;
		}
	}
	for(int i = 0; i < n; ++i)
		if((a * i - b * ((n * (n - 1LL) >> 1) - i) - s) % n == 0)
		{
			ans += f[n - 1][i];
			if(ans >= mod)
				ans -= mod;
		}
	printf("%d\n", ans);
	return 0;
}
