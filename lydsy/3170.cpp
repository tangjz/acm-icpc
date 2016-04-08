/*
 * 切比雪夫距离转化成曼哈顿距离 直接算 
 */ 
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n;
long long ans[maxn];
struct Node { int v, id; } x[maxn], y[maxn];
bool cmp(const Node &x, const Node &y) { return x.v < y.v; }
int main()
{
	int i, j, xx, yy;
	long long sum1, sum2;
	scanf("%d", &n);
	for(i = 1; i <= n; ++i)
	{
		scanf("%d%d", &xx, &yy);
		x[i] = (Node){xx + yy, i};
		y[i] = (Node){xx - yy, i};
	}
	sort(x + 1, x + n + 1, cmp);
	sum1 = sum2 = 0;
	for(i = 1; i <= n; ++i) sum1 += x[i].v;
	for(i = 1; i <= n; ++i)
	{
		ans[x[i].id] += sum1 + (long long)x[i].v * ((i - 1 << 1) - n) - sum2;
		sum1 -= x[i].v;
		sum2 += x[i].v;
	}
	sort(y + 1, y + n + 1, cmp);
	sum1 = sum2 = 0;
	for(i = 1; i <= n; ++i) sum1 += y[i].v;
	for(i = 1; i <= n; ++i)
	{
		ans[y[i].id] += sum1 + (long long)y[i].v * ((i - 1 << 1) - n) - sum2;
		sum1 -= y[i].v;
		sum2 += y[i].v;
	}
	for(i = 2, j = 1; i <= n; ++i) if(ans[i] < ans[j]) j = i;
	printf("%lld\n", ans[j] >> 1);
	return 0;
}
