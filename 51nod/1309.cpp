#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50001, mod = 1000000007;
int n, q, a[maxn], s[maxn], inv[maxn], perms;
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
	{
		s[i] = s[i - 1] + a[i];
		if(s[i] >= mod)
			s[i] -= mod;
	}
	inv[1] = 1;
	for(int i = 2; i <= n + 1; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	perms = 1;
	for(int i = 2, o = 1; i <= n; ++i)
	{
		o = a[i - 1] == a[i] ? o + 1 : 1;
		perms = (LL)perms * inv[o] % mod * i % mod;
	}
	while(q--)
	{
		int x;
		scanf("%d", &x);
		x = lower_bound(a + 1, a + n + 1, x + 1) - a - 1;
		printf("%d\n", (LL)s[x] * perms % mod * inv[n + 1 - x] % mod);
	}
	return 0;
}
