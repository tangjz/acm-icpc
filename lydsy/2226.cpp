/*
 * 合并gcd(i, n)相同项 
 * ans = n * ∑（p | n) p * phi(p) / 2 
 */
#include <cstdio>
const int maxn = 1000001;
int t, n, vis[maxn], prime[maxn], tot = 0, sum, f[maxn], s[maxn];
long long phi[maxn], ans;
void dfs(int dep, int now)
{
	if(dep > sum) { ans += n * phi[n / now]; return; }
	dfs(dep + 1, now);
	for(int i = 1; i <= s[dep]; ++i) dfs(dep + 1, now *= f[dep]);
}
int main()
{
	int i, j, k;
	for(i = 2; i < maxn; ++i)
	{
		if(!vis[i]) { vis[i] = prime[tot++] = i; phi[i] = i - 1; }
		for(j = 0; j < tot && i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = prime[j];
			if(i % prime[j] == 0) { phi[i * prime[j]] = phi[i] * prime[j]; break; }
			else phi[i * prime[j]] = phi[i] * phi[prime[j]];
		}
	}
	for(phi[1] = 1, i = 3; i < maxn; ++i) phi[i] = phi[i] * i >> 1;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(sum = ans = 0, i = n; i != 1; )
			for(f[++sum] = j = vis[i], s[sum] = 0; i % j == 0; ++s[sum]) i /= j;
		dfs(1, 1);
		printf("%lld\n", ans);
	}
	return 0;
}
