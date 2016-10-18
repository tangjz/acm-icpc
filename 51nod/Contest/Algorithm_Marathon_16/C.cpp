#include <stdio.h>
typedef long long LL;
const int maxn = 1000001, maxm = 17, mod = 1000000007;
int n, m, a[maxm], b[maxm], fact[maxn], iact[maxn], pos[maxn], ans;
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
void dfs(int dep, int cnt, int sum, int val)
{
	if(dep == m)
	{
		ans = (ans + (LL)val * iact[n - 2 - sum] % mod * mod_pow(n - cnt, n - 2 - sum)) % mod;
		return;
	}
	dfs(dep + 1, cnt, sum, val);
	if(!pos[a[dep]])
	{
		pos[a[dep]] = b[dep];
		val = (LL)val * iact[b[dep] - 1] % mod;
		if(val)
			val = mod - val;
		dfs(dep + 1, cnt + 1, sum + b[dep] - 1, val);
		pos[a[dep]] = 0;
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		scanf("%d%d", a + i, b + i);
	if(n == 1)
	{
		ans = !m || !b[0];
		printf("%d\n", ans);
		return 0;
	}
	iact[1] = 1;
	for(int i = 2; i <= n; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	fact[0] = iact[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	dfs(0, 0, 0, fact[n - 2]);
	printf("%d\n", ans);
	return 0;
}
