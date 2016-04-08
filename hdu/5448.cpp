#include <stdio.h>
typedef long long LL;
const int maxn = 100010, mod = 1000000007, inv2 = 500000004;
int t, n, pw[maxn], x, y, pre1x, pre1y, pre2x, pre2y, ans;
inline int mod_add(int x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
	return x;
}
inline int mod_sub(int x, int y)
{
	x -= y;
	if(x < 0)
		x += mod;
	return x;
}
inline int det(int x1, int y1, int x2, int y2)
{
	return mod_sub((LL)x1 * y2 % mod, (LL)x2 * y1 % mod);
}
int main()
{
	scanf("%d", &t);
	pw[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		pw[i] = pw[i - 1] << 1;
		if(pw[i] >= mod)
			pw[i] -= mod;
	}
	while(t--)
	{
		scanf("%d", &n);
		pre1x = pre1y = pre2x = pre2y = ans = 0;
		for(int i = 1, pw2 = inv2; i <= n; ++i, pw2 = (LL)pw2 * inv2 % mod)
		{
			scanf("%d%d", &x, &y);
			ans = mod_add(ans, (LL)pw[i - 1] * det(x, y, pre2x, pre2y) % mod);
			ans = mod_add(ans, (LL)(i == n ? inv2 : pw[n - i - 1]) * det(pre1x, pre1y, x, y) % mod);
			pre1x = mod_add(pre1x, (LL)x * pw[i] % mod); // +
			pre1y = mod_add(pre1y, (LL)y * pw[i] % mod); // +
			pre2x = mod_add(pre2x, (LL)x * pw2 % mod); // -
			pre2y = mod_add(pre2y, (LL)y * pw2 % mod); // -
		}
		printf("%d\n", ans);
	}
	return 0;
}
