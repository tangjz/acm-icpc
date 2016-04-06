#include <cstdio>
#include <cstring>
const int maxn = 501, maxm = 4096;
int t, n, f[2][maxm];
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		int cur = 0, nxt = 1;
		scanf("%d", &n);
		memset(f[cur], -1, sizeof(f[0]));
		f[cur][0] = 0;
		for(int i = 0, x; i < n; ++i)
		{
			scanf("%d", &x);
			memcpy(f[nxt], f[cur], sizeof(f[0]));
			for(int j = 0; j < maxm; ++j)
			{
				if(f[cur][j] == -1)
					continue;
				int lowbit = j & -j;
				if(lowbit > x)
					upd(f[nxt][j | x], f[cur][j] + x);
				else if(lowbit == x)
				{
					int bonus = 0;
					for(int k = x; j & k; k <<= 1)
						bonus += k << 1;
					upd(f[nxt][(j + x) & (maxm - 1)], f[cur][j] + x + bonus);
				}
				else
					upd(f[nxt][x], f[cur][j] + x);
			}
			cur ^= 1;
			nxt ^= 1;
		}
		int ans = 0;
		for(int i = 0; i < maxm; ++i)
			upd(ans, f[cur][i]);
		printf("%d\n", ans);
	}
	return 0;
}
