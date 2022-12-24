#include <cstdio>
typedef long long LL;
const int mod = 1000007;
int n, x, a, ans;
int main()
{
	while(scanf("%d%d%d", &n, &x, &ans) == 3)
	{
		for(int i = 1, p = 1; i <= n; ++i)
		{
			scanf("%d", &a);
			p = (LL)p * x % mod;
			ans = (ans + (LL)a * p) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
