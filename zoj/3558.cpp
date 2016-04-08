#include <cstdio>
const int mod = 100000007;
typedef long long LL;
int n, sqn, ans1, ans2;
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
void dec(int &x, int y)
{
	x -= y;
	if(x < 0)
		x += mod;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		ans1 = ans2 = 0;
		for(sqn = 1; (LL)sqn * sqn <= n; ++sqn); --sqn;
		for(int i = 1; i <= sqn; ++i)
			inc(ans1, n / i % mod);
		inc(ans1, ans1);
		dec(ans1, sqn * sqn % mod);
		ans1 = (LL)ans1 * n % mod;
		for(int i = 1; i <= sqn; ++i)
			inc(ans2, (LL)i * (i + n / i) * (n / i + 1 - i) % mod);
		dec(ans2, (LL)sqn * (sqn + 1) * (2 * sqn + 1) / 6 % mod);
		dec(ans1, ans2);
		printf("%d\n", ans1);
	}
	return 0;
}
