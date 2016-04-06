#include <cstdio>
typedef long long LL;
const int maxn = 1000000, mod = 1000000007;
int n, m, inv[maxn], ans;
int main()
{
	scanf("%d%d", &n, &m);
	--n;
	--m;
	inv[1] = 1;
	for(int i = 2; i <= m; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	ans = 1;
	for(int i = 1; i <= m; ++i)
		ans = (LL)ans * (n + i) % mod * inv[i] % mod;
	printf("%d\n", ans);
	return 0;
}
