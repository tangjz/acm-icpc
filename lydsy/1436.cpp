#include <cstdio>
typedef long long LL;
const int mod = 3;
int c[mod][mod];
int C(LL n, LL m)
{
	int ret = 1;
	for( ; n && ret; n /= mod, m /= mod)
		ret = ret * c[n % mod][m % mod] % mod;
	return ret;
}
int main()
{
	for(int i = 0; i < mod; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			if((c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod)
				c[i][j] -= mod;
	}
	int t;
	LL n, m;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &n, &m);
		int ans = C(n << 1, m);
		if((m & 1) && ans)
			ans = mod - ans;
		printf("%d\n", ans);
	}
	return 0;
}
