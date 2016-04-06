#include <cstdio>
const int maxn = 1000001, maxs = 101, mod = 1000000007;
int a, b, n, tot, sum[maxs], inv[maxn], fact[maxn], ans;
void dfs(int dep, int num)
{
	if(num >= n * a && num <= n * b)
		sum[tot++] = num;
	if(dep == 7)
		return;
	dfs(dep + 1, num * 10 + a);
	dfs(dep + 1, num * 10 + b);
}
int main()
{
	scanf("%d%d%d", &a, &b, &n);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
	inv[0] = fact[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i] = (long long)fact[i - 1] * i % mod;
		inv[i] = (long long)inv[i] * inv[i - 1] % mod;
	}
	dfs(0, 0);
	for(int i = 0; i < tot; ++i)
		if((sum[i] - n * a) % (b - a) == 0)
		{
			int j = (sum[i] - n * a) / (b - a);
			ans += (long long)fact[n] * inv[j] % mod * inv[n - j] % mod;
			if(ans >= mod)
				ans -= mod;
		}
	printf("%d\n", ans);
	return 0;
}
