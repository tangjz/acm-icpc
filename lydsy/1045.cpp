/*
 * 设平均数为k, sum[x] = ∑(i = 1 to x) num[i] - x
 * 则ans = ∑(x = 1 to n) sum[x] - sum[y]
 * 当sum[y]为中位数时ans最小 排序
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
