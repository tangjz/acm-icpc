/*
 * 问一群和为n的数的最小公倍数有多少种可能
 * 若两个数不互质，那么把公约数单独列出来，其它部分用1填充，最小公倍数相同
 * 筛出质数往背包里填
 */
#include <cstdio>
int n, prime[1001] = {}, cnt = 0;
long long f[1001] = {}, ans = 0;
bool flag[1001] = {};
int main()
{
	int i, j, k;
	scanf("%d", &n);
	for(i = 2; i <= n; ++i)
		if(!flag[i])
		{
			prime[++cnt] = i;
			for(j = i << 1; j <= n; j += i) flag[j] = true;
		}
	f[0] = 1;
	for(i = 1; i <= cnt; ++i)
		for(j = n; j >= 2; --j)
			for(k = prime[i]; k <= j; k *= prime[i]) f[j] += f[j - k];
	for(i = 0; i <= n; ++i) ans += f[i];
	printf("%lld\n", ans);
	return 0;
}
