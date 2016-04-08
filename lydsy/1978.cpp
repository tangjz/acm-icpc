/*
 * 令f[t, i]表示枚举到第t个数，以含约数i的数结尾最多取数的个数 
 * 对于当前数x可以找到max{f[t - 1, k] + 1}(k | x && k >= l)
 * 再次更新f[t, k](k | x)和ans
 * 第一维可以滚动掉 
 */
#include <cstdio>
const int maxv = 1000001, maxsqv = 1001;
int n, l, f[maxv], g[maxsqv], ans;
inline void update(int &x, int y) { if(x < y) x = y; }
int main()
{
	scanf("%d%d", &n, &l);
	while(n--)
	{
		int x, Max = g[0] = 0;
		scanf("%d", &x);
		for(int i = 1; i * i <= x; ++i)
			if(x % i == 0)
			{
				g[++g[0]] = i;
				if(i >= l) update(Max, f[i]);
				g[++g[0]] = x / i;
				if(x / i >= l) update(Max, f[x / i]);
			}
		update(ans, ++Max);
		for(int i = 1; i <= g[0]; ++i)
			update(f[g[i]], Max);
	}
	printf("%d\n", ans);
	return 0;
}
