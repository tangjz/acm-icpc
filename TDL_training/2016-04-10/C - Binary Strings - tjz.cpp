#include <cstdio>
typedef long double LDB;
const int maxn = 100010, mod = 3;
int t, n;
char str[maxn];
double f[maxn][mod], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%s", &n, str + 1);
		ans = 0;
		for(int i = 1; str[i]; ++i)
		{
			for(int j = 0; j < mod; ++j)
				f[i][j] = 0;
			if(str[i] == '0' || str[i] == '?')
			{
				for(int j = 0; j < mod; ++j)
					f[i][(j * 2) % mod] += f[i - 1][j];
				ans += 1;
			}
			if(str[i] == '1' || str[i] == '?')
			{
				for(int j = 0; j < mod; ++j)
					f[i][(j * 2 + 1) % mod] += f[i - 1][j];
				f[i][1] += 1;
			}
			if(str[i] == '?')
			{
				for(int j = 0; j < mod; ++j)
					f[i][j] = f[i][j] * 0.5;
				ans -= 0.5;
			}
			ans += f[i][0];
		}
		printf("%.2f\n", ans);
	}
	return 0;
}
