#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 20, maxm = 100001, mod = 1000000007;
int n, m, f[2][1 << 20][2], cur, pre = 1, ans;
inline void mod_inc(int &x, int y)
{
	if((x += y) >= mod)
		x -= y;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
	{
		int val, sz, x, msk = 0;
		scanf("%d%d", &val, &sz);
		while(sz--)
		{
			scanf("%d", &x);
			msk |= 1 << (--x);
		}
		f[cur][msk][0] += val;
	}
	for(int i = 0; i < n; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		memset(f[cur], 0, (1 << n + 1) * sizeof(int));
		for(int msk = 0; msk < 1 << n; ++msk)
		{
			mod_inc(f[cur][msk & ~(1 << i)][0], f[pre][msk][0]);
			mod_inc(f[cur][msk & ~(1 << i)][1], f[pre][msk][1]);
			mod_inc(f[cur][msk | (1 << i)][0], f[pre][msk][(msk >> i) & 1]);
			mod_inc(f[cur][msk | (1 << i)][1], f[pre][msk][~(msk >> i) & 1]);
		}
	}
	for(int i = 1; i < 1 << n; ++i)
		ans = (ans + (LL)f[cur][i][1] * f[cur][i][1]) % mod;
	printf("%d\n", ans);
	return 0;
}
