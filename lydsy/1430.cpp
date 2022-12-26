/*
 * 带标号n点的生成树个数为n ^ (n - 2)
 * 此题还有加边顺序
 */
#include <cstdio>
typedef long long LL;
const int mod = 9999991;
int n, ans = 1;
int main()
{
	scanf("%d", &n);
	for(int i = 2; i < n; ++i)
		ans = ans * (LL)i % mod;
	int x = n, k = n - 2;
	while(k)
	{
		if(k & 1) ans = ans * (LL)x % mod;
		x = x * (LL)x % mod;
		k >>= 1;
	}
	printf("%d\n", ans);
	return 0;
}
