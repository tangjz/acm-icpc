/*
 * 直接枚举约数 ans = ∑p * phi(n / p)
 */
#include <cstdio>
int sum;
long long n, f[40], s[40], ans = 0;
long long phi(long long x)
{
	long long res = x;
	for(int i = 1; i <= sum; ++i)
		if(x % f[i] == 0) res = res / f[i] * (f[i] - 1);
	return res;
}
void dfs(int dep, long long now)
{
	if(dep > sum)
	{
		ans += now * phi(n / now);
		return;
	}
	dfs(dep + 1, now);
	for(int i = 1; i <= s[dep]; ++i) dfs(dep + 1, now *= f[dep]);
}
int main()
{
	scanf("%lld", &n);
	long long tmp = n;
	for(long long i = 2; i * i <= tmp && tmp > 1; ++i)
		if(tmp % i == 0)
			for(f[++sum] = i; tmp % i == 0; ++s[sum]) tmp /= i;
	if(tmp > 1) { f[++sum] = tmp; s[sum] = 1; }
	dfs(1, 1);
	printf("%lld\n", ans);
	return 0;
}
