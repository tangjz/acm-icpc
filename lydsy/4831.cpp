#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxm = 1000001, INF = 0x3f3f3f3f;
inline void upd_max(int &x, int y)
{
	if(x < y)
		x = y;
}
inline void upd_min(int &x, int y)
{
	if(x > y)
		x = y;
}
int t, n, a[maxn], f[2][maxm][2], g[2][maxm][2], cur, nxt = 1;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		a[0] = f[cur][0][0] = g[cur][0][0] = 0;
		f[cur][0][1] = -1;
		g[cur][0][1] = INF;
		for(int i = 1; i <= n; ++i, cur ^= 1, nxt ^= 1)
		{
			scanf("%d", a + i);
			memset(f[nxt], -1, (a[i] + 1 << 1) * sizeof(int));
			memset(g[nxt], 0x3f, (a[i] + 1 << 1) * sizeof(int));
			for(int j = 0, lim = std::min(a[i - 1], a[i]); j <= lim; ++j)
			{
				if(f[cur][j][0] != -1)
					upd_max(f[nxt][a[i] - j][0], f[cur][j][0] + j);
				if(f[cur][j][1] != -1)
					upd_max(f[nxt][a[i] - j][0], f[cur][j][1] + j);
				if(g[cur][j][0] != INF)
					upd_min(g[nxt][a[i] - j][0], g[cur][j][0] + j);	
				if(g[cur][j][1] != INF)
					upd_min(g[nxt][a[i] - j][0], g[cur][j][1] + j);	
			}
			int tf = -1, tg = INF;
			for(int j = a[i] + 1; j <= a[i - 1]; ++j)
			{
				if(f[cur][j][0] != -1)
				{
					upd_max(tf, f[cur][j][0]);
					upd_max(f[nxt][0][0], f[cur][j][0] + a[i]);
				}
				if(g[cur][j][0] != INF)
				{
					upd_min(tg, g[cur][j][0]);
					upd_min(g[nxt][0][0], g[cur][j][0] + a[i]);	
				}
			}
			for(int j = std::min(a[i - 1], a[i]); j >= 0; --j)
			{
				if(tf != -1)
					upd_max(f[nxt][a[i] - j][1], tf + j);
				if(tg != INF)
					upd_min(g[nxt][a[i] - j][1], tg + j);
				upd_max(tf, f[cur][j][0]);
				upd_min(tg, g[cur][j][0]);
			}
		}
		int af = f[cur][0][1], ag = g[cur][0][1];
		for(int i = 0; i <= a[n]; ++i)
		{
			upd_max(af, f[cur][i][0]);
			upd_min(ag, g[cur][i][0]);
		}
		printf("%d %d\n", ag, af);
	}
	return 0;
}
