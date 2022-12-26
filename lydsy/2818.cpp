/*
 * 设f[k]表示1 <= x, y <= k中gcd(x, y) = 1的有序对个数
 * 则f[k] = 2 * ∑(1 < i <= k)(phi[i]) + 1
 * 所以 ans = ∑f[n / prime]
 */
#include <cstdio>
int n, m, prime[664580], cnt = 0;
long long sum[10000001], ans = 0;
bool visited[10000001] = {};
int main()
{
	int i, j;
	scanf("%d", &n);
	sum[1] = 1;
	for(i = 2; i <= 10000000; ++i)
	{
		if(!visited[i]) { prime[++cnt] = i; sum[i] = i - 1; }
		for(j = 1; j <= cnt && prime[j] * i <= 10000000; ++j)
		{
			visited[prime[j] * i] = true;
			if(i % prime[j] == 0) { sum[prime[j] * i] = sum[i] * prime[j]; break; }
			else sum[prime[j] * i] = sum[i] * (prime[j] - 1);
		}
	}
	for(i = 2; i <= 10000000; ++i) sum[i] += sum[i - 1];
	for(i = 1; i <= cnt; ++i) ans += (sum[n / prime[i]] - 1) * 2 + 1;
	printf("%lld\n", ans);
	return 0;
}
