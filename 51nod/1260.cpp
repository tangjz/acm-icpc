#include <stdio.h>
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
int n, inv[maxn], pre, cur, ans;
int main()
{
	scanf("%d", &n);
	if(!(--n))
	{
		puts("1");
		return 0;
	}
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	pre = 1;
	for(int i = 1, pw2 = 2; i <= n; ++i)
	{
		cur = (LL)pre * (n - i + 1) % mod * inv[i] % mod;
		ans = (ans + (LL)pre * cur % mod * pw2) % mod;
		pre = cur;
		if((pw2 += pw2) >= mod)
			pw2 -= mod;
	}
	ans = (LL)ans * inv[n] % mod;
	printf("%d\n", ans);
	return 0;
}
