#include <cstdio>
#include <cstring>
const int maxn = 1010, maxs = 256, mod = 100007;
int T, n, f[maxn][maxn];
char s[maxn];
int main()
{
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		memset(f, 0, sizeof f);
		for(int i = 1; i <= n; ++i)
			f[i][i] = 1;
		for(int d = 2; d <= n; ++d)
			for(int i = 1; i <= n - d + 1; ++i)
			{
				int j = i + d - 1;
				f[i][j] = f[i + 1][j] + f[i][j - 1];
				if(s[i] == s[j])
					++f[i][j];
				else
					f[i][j] += mod - f[i + 1][j - 1];
				f[i][j] %= mod;
			}
		printf("Case #%d: %d\n", Case, f[1][n]);
	}
	return 0;
}

