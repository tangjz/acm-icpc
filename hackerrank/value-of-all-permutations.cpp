#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int mod, n, q, a[maxn], s[maxn], inv[maxn], perms;
int main()
{
	scanf("%d%d", &mod, &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
		s[i] = (s[i - 1] + a[i]) % mod;
	inv[1] = 1;
	for(int i = 2; i <= n + 1; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	perms = 1;
	for(int i = 2, o = 1; i <= n; ++i)
	{
		o = a[i - 1] == a[i] ? o + 1 : 1;
		perms = (LL)perms * inv[o] % mod * i % mod;
	}
	scanf("%d", &q);
	while(q--)
	{
		int x;
		scanf("%d", &x);
		x = lower_bound(a + 1, a + n + 1, x + 1) - a - 1;
		printf("%d\n", (int)((LL)s[x] * perms % mod * inv[n + 1 - x] % mod));
	}
	return 0;
}
