/*
 * 双倍经验 ： 代码及数据见 1045
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
long long sum[1000001] = {}, ans = 0;
int main()
{
	int i;
	long long tmp;
	scanf("%d", &n);
	for(i = 1; i <= n; ++i)
	{
		scanf("%lld", &tmp);
		sum[i] = sum[i - 1] + tmp;
	}
	tmp = sum[n] / n;
	for(i = 1; i <= n; ++i) sum[i] -= tmp * i;
	sort(sum + 1, sum + n + 1);
	tmp = sum[(n + 1) >> 1];
	for(i = 1; i <= n; ++i) ans += abs(sum[i] - tmp);
	printf("%lld\n", ans);
	return 0;
}
