#include <cstdio>
#include <cstring>
const int maxn = 1001, maxm = 11, maxe = 51, maxd = 4, pw[maxd] = {0, 4, 8, 11}, INF = 0x3f3f3f3f;
int t, n, m, e, a[maxn], s[maxn], f[2][maxe][maxm][maxd], pre = 1, cur, ans;
inline void upd(int &x, int y)
{
	if(x > y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d", &n, &m, &e);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			s[i] = s[i - 1] + a[i];
		}
		ans = s[n];
		memset(f[cur], 0x3f, (e + 1) * sizeof(f[0][0]));
		f[cur][e][0][0] = 0;
		for(int i = 1, val; i <= n; ++i)
		{
			pre ^= 1;
			cur ^= 1;
			memset(f[cur], 0x3f, (e + 1) * sizeof(f[0][0]));
			for(int x = 0; x <= e; ++x)
				for(int y = 0; y <= m; ++y)
					for(int z = 0; z < maxd; ++z)
					{
						if(f[pre][x][y][z] == INF)
							continue;
						for(int w = 0; w < maxd && w <= x; ++w)
						{
							int v = y + (z != w);
							if(v <= m)
								upd(f[cur][x - w][v][w], f[pre][x][y][z] + (a[i] > pw[w] ? a[i] - pw[w] : 0));
						}
					}
			for(int x = 0; x <= e; ++x)
				for(int y = 0; y <= m; ++y)
					for(int z = 0; z < maxd; ++z)
						upd(ans, f[cur][x][y][z] + s[n] - s[i]);
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
