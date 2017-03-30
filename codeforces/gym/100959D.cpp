#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 2001, mod = (int)1e9 + 7;
int n, a[2][maxn], rk[2][maxn], f[2][maxn][3], cur, pre = 1;
inline void mod_inc(int &x, int y)
{
	(x += y) >= mod && (x -= mod);
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			scanf("%d", a[i] + j);
			rk[i][a[i][j]] = j;
		}
	}
	if(a[0][1] == a[1][1])
		f[cur][a[0][1]][2] = 1;
	else
		f[cur][a[0][1]][0] = f[cur][a[1][1]][1] = 1;
	for(int i = 2; i <= n << 1; ++i)
	{
		cur ^= 1;
		pre ^= 1;
		memset(f[cur], 0, sizeof f[0]);
		for(int j = 1; j <= n; ++j)
			for(int k = 0; k < 3; ++k)
			{
				if(!f[pre][j][k])
					continue;
				int len = 0, p[2][2];
				if((k + 1) & 1)
				{
					p[len][0] = rk[0][j];
					p[len][1] = i - 1 - p[len][0];
					++len;
				}
				if((k + 1) >> 1)
				{
					p[len][1] = rk[1][j];
					p[len][0] = i - 1 - p[len][1];
					++len;
				}
				int tot = 0, nxt[4];
				for(int x = 0; x < len; ++x)
					for(int y = 0; y < 2; ++y)
						if(p[x][y] < n)
							nxt[tot++] = a[y][p[x][y] + 1];
				std::sort(nxt, nxt + tot);
				tot = std::unique(nxt, nxt + tot) - nxt;
				for(int o = 0; o < tot; ++o)
				{
					int val = nxt[o], msk = 0;
					for(int x = 0; x < len; ++x)
						for(int y = 0; y < 2; ++y)
							msk |= (p[x][y] < n && a[y][p[x][y] + 1] == val) << y;
					if(msk)
						mod_inc(f[cur][val][msk - 1], f[pre][j][k]);
				}
			}
	}
	int ans = 0;
	if(a[0][n] == a[1][n])
		for(int i = 0; i < 3; ++i)
			mod_inc(ans, f[cur][a[0][n]][i]);
	else
		for(int i = 0; i < 2; ++i)
			mod_inc(ans, f[cur][a[i][n]][i]);
	printf("%d\n", ans);
	return 0;
}
