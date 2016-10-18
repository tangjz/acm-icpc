#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxd = 41;
int n, m, len[maxn], f[maxn][maxd], g[maxn][maxd], l[maxn], r[maxn], out[maxn];
inline bool valid(int r1, int m1, int r2, int m2)
{
	int g = std::__gcd(m1, m2);
	return (r1 % g) == (r2 % g);
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(r, -1, sizeof r);
	for(int i = 1; i <= m; ++i)
		memset(f[i], -1, sizeof f[0]);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", len + i);
		for(int j = 0, x; j < len[i]; ++j)
		{
			scanf("%d", &x);
			int *F = f[x], *G = g[x], &L = l[x], &R = r[x], &ans = out[x];
			if(R != i - 1)
				L = i;
			R = i;
			for(int m = 1; m < maxd; ++m)
				if(F[m] >= 0 && !valid(j, len[i], F[m], m) && L <= G[m])
					L = G[m] + 1;
			F[len[i]] = j;
			G[len[i]] = i;
			for(int m = 1; m < maxd; ++m)
				if(F[m] >= 0 && G[m] < L)
					F[m] = -1;
			if(ans < i - L + 1)
				ans = i - L + 1;
		}
	}
	for(int i = 1; i <= m; ++i)
		printf("%d\n", out[i]);
	return 0;
}
