/*
 * 求gcd(i, j) = 1的个数 
 */
#include <cstdio>
int n, prime[40001], tot = 0, phi[40001];
bool vis[40001];
long long ans;
int main()
{
	int i, j;
	scanf("%d", &n);
	for(i = 2; i <= n; ++i)
	{
		if(!vis[i]) { vis[i] = true; prime[tot++] = i; phi[i] = i - 1; }
		for(j = 0; j < tot && i * prime[j] <= n; ++j)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0) { phi[i * prime[j]] = phi[i] * prime[j]; break; }
			else phi[i * prime[j]] = phi[i] * phi[prime[j]];
		}
	}
	for(i = 2; i < n; ++i) ans += phi[i] << 1;
	printf("%lld\n", ans + 3);
	return 0;
}
