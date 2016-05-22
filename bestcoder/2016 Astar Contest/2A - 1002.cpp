#include <stdio.h>
#include <cstring>
const int maxn = 16;
const long long INF = ~0ull >> 1;
int t, n, a[maxn], pos[maxn], sz[1 << maxn], lbit[1 << maxn];
long long f[1 << maxn][maxn];
inline void upd(long long &x, long long y)
{
	if(x < y)
		x = y;
}
int main()
{
	for(int i = 1; i < 1 << maxn; ++i)
	{
		sz[i] = sz[i >> 1] + (i & 1);
		lbit[i] = i & 1 ? 0 : lbit[i >> 1] + 1;
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		memset(pos, -1, n * sizeof(int));
		for(int i = 0; i < n; ++i)
		{
			int x;
			scanf("%d%d", a + i, &x);
			pos[x] = i;
		}
		for(int i = 1; i < 1 << n; ++i)
		{
			if(sz[i] == 1)
			{
				f[i][lbit[i]] = pos[0] == -1 || pos[0] == lbit[i] ? 0 : -INF;
				continue;
			}
			for(int r = i, j = lbit[r]; r > 0; r ^= 1 << j, j = lbit[r])
			{
				int o = i ^ (1 << j);
				f[i][j] = -INF;
				if(pos[sz[o]] != -1 && pos[sz[o]] != j)
					continue;
				for(int s = o, k = lbit[s]; s > 0; s ^= 1 << k, k = lbit[s])
					if(f[o][k] != -INF)
						upd(f[i][j], f[o][k] + (long long)a[k] * a[j]);
			}
		}
		long long ans = -INF;
		for(int i = 0; i < n; ++i)
			upd(ans, f[(1 << n) - 1][i]);
		printf("Case #%d:\n%I64d\n", Case, ans);
	}
	return 0;
}
