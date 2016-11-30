#include <cstdio>
#include <cstring>
int n, m, mod, r[555], cnt[2], f[555][555];
char str[555];
int main()
{
	while(scanf("%d%d%d", &n, &m, &mod) == 3)
	{
		memset(r, 0, sizeof r);
		memset(cnt, 0, sizeof cnt);
		memset(f, 0, sizeof f);
		for(int i = 0; i < m; ++i)
		{
			scanf("%s", str);
			for(int j = 0; j < n; ++j)
				if(str[j] == '1')
					++r[j];
		}
		for(int i = 0; i < n; ++i)
			++cnt[r[i]];
		f[0][0] = 1;
		for(int i = 0; i <= cnt[0]; ++i)
			for(int j = 0; j <= n; ++j)
			{
				if(i >= 2 && j + 2 <= n)
				{
					f[i][j] += (long long)i * (i - 1) / 2 * f[i - 2][j + 2] % mod;
					if(f[i][j] >= mod)
						f[i][j] -= mod;
				}
				if(j >= 2)
				{
					f[i][j] += (long long)j * (j - 1) / 2 * f[i][j - 2] % mod;
					if(f[i][j] >= mod)
						f[i][j] -= mod;
				}
				if(i && j)
				{
					f[i][j] += (long long)i * j * f[i - 1][j] % mod;
					if(f[i][j] >= mod)
						f[i][j] -= mod;
				}
			}
		printf("%d\n", f[cnt[0]][cnt[1]]);
	}
	return 0;
}
