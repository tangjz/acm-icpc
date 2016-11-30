#include <cstdio>
#include <cstring>
const int maxn = 9, maxnn = 65;
int t, n, m, sum;
long long c[maxnn][maxnn];
bool vis[maxn][maxn];
double ans;
char str[maxn][maxn];
int main()
{
	for(int i = 0; i < maxnn; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	scanf("%d", &t);
	while(t--)
	{
		sum = 0;
		ans = 0;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", str[i]);
			for(int j = 0; j < n; ++j)
				if(str[i][j] == '.')
					++sum;
		}
		for(int s = 1; s < 1 << n + n + 2; ++s)
		{
			int cnt = 0, tot = 0;
			memset(vis, 0, sizeof vis);
			for(int i = 0; i < n; ++i)
				if(s & (1 << i))
				{
					++tot;
					for(int j = 0; j < n; ++j)
						vis[i][j] = 1;
				}
			for(int i = 0; i < n; ++i)
				if(s & (1 << n + i))
				{
					++tot;
					for(int j = 0; j < n; ++j)
						vis[j][i] = 1;
				}
			if(s & (1 << n + n))
			{
				++tot;
				for(int i = 0; i < n; ++i)
					vis[i][i] = 1;
			}
			if(s & (1 << n + n + 1))
			{
				++tot;
				for(int i = 0; i < n; ++i)
					vis[i][n - i - 1] = 1;
			}
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					if(vis[i][j] && str[i][j] == '.')
						++cnt;
			if(cnt <= m)
				ans += (tot & 1 ? 1.0 : -1.0) * c[sum - cnt][m - cnt] / c[sum][m];
		}
		printf("%.9f\n", ans * 100);
	}
	return 0;
}
