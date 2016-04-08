/*
 * |x1 - x2| + |y1 - y2| = max(|(x1 + y1) - (x2 + y2)|, |(x1 - y1) - (x2 - y2)|)
 * 首先将切比雪夫距离转化为曼哈顿距离，x与y分开统计中位数 
 * 将答案转回切比雪夫距离，有可能不是整点，于是扰乱一下检查，找最小值 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int ch;
template<typename _> inline void getint(_ &t)
{
	while((ch = getchar()) < '0' || ch > '9');
	t = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		t = (t << 3) + (t << 1) + ch - '0';
}
typedef long long LL;
const int maxn = 100001;
int n, x[maxn], y[maxn];
double a[maxn], b[maxn];
LL ans = ~0ull >> 1;
void check(int mx, int my)
{
	LL sum = 0;
	for(int i = 0; i < n; ++i)
		sum += max(abs(mx - x[i]), abs(my - y[i]));
	if(ans > sum) ans = sum;
}
int main()
{
	getint(n);
	for(int i = 0; i < n; ++i)
	{
		getint(x[i]), getint(y[i]); 
		a[i] = (x[i] + y[i]) / 2.0;
		b[i] = (x[i] - y[i]) / 2.0;
	}
	sort(a, a + n);
	sort(b, b + n);
	double mx = a[n - 1 >> 1] + b[n - 1 >> 1], my = a[n - 1 >> 1] - b[n - 1 >> 1];
	for(int i = -1; i <= 1; ++i)
		for(int j = -1; j <= 1; ++j)
			check(mx + i, my + j);
	printf("%lld\n", ans); 
	return 0;
}
