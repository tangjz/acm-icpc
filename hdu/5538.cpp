#include <cstdio>
const int maxn = 52;
int t, n, m, h[maxn][maxn], ans;
inline int abs(int x)
{
	return x < 0 ? -x : x;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= m; ++j)
			{
				scanf("%d", h[i] + j);
				if(h[i][j])
					++ans;
			}
			h[i][m + 1] = 0;
		}
		for(int i = 1; i <= m; ++i)
			h[n + 1][i] = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m + 1; ++j)
				ans += abs(h[i][j] - h[i][j - 1]);
		for(int i = 1; i <= n + 1; ++i)
			for(int j = 1; j <= m; ++j)
				ans += abs(h[i][j] - h[i - 1][j]);
		printf("%d\n", ans);
	}
	return 0;
}
