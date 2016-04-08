#include <cstdio>
const int maxn = 21, mod = 1000000007;
typedef long long LL;
int n, inv[maxn];
LL m, a[maxn], ans;
int C(LL n, int m)
{
	int ret = inv[m];
	for(int i = 0; i < m; ++i)
		ret = (n - i) % mod * ret % mod;
	return ret;
}
void dfs(int dep, LL cnt, int sgn)
{
	if(dep == n)
	{
		ans += sgn * C(m - cnt + n - 1, n - 1);
		return;
	}
	dfs(dep + 1, cnt, sgn);
	if(cnt + a[dep] + 1 <= m)
		dfs(dep + 1, cnt + a[dep] + 1, -sgn);
}
int main()
{
	scanf("%d%lld", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%lld", a + i);
	inv[1] = 1;
	for(int i = 2; i < n; ++i)
		inv[i] = mod - (LL)mod / i * inv[mod % i] % mod;
	inv[0] = 1;
	for(int i = 1; i < n; ++i)
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	dfs(0, 0, 1);
	ans %= mod;
	if(ans < 0)
	    ans += mod;
	printf("%d\n", (int)ans);
	return 0;
}
