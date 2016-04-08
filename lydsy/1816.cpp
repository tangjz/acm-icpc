/*
 * 假设n+1种牌都有至少m张 那么共(n + 1) * m张 设实际不足的牌有s张 
 * m副牌共有n * m张 那么只要满足(n + 1) * m - s >= n * m即s <= m
 */
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF = ~0u >> 1;
int n;
long long num[101], l, r, mid, sum;
int main()
{
	int i;
	scanf("%d", &n);
	++n;
	for(i = 0; i < n; ++i) scanf("%lld", &num[i]);
	sort(num, num + n);
	l = 0; r = INF;
	while(l + 1 < r)
	{
		mid = (l + r) >> 1; sum = 0;
		for(i = 0; i < n; ++i) if(num[i] < mid) sum += mid - num[i];
		if(sum <= mid) l = mid;
		else r = mid;
	}
	printf("%lld\n", l);
	return 0;
}
