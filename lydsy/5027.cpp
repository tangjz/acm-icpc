#include <cstdio>
#include <algorithm>
using namespace std;
int exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
int a, b, c, x1, x2, y1, y2, x, y, r;
long long tl, tr;
void check(long long l, long long r, int d)
{
	if(d < 0)
	{
		d = -d;
		long long t = -l;
		l = -r;
		r = t;
	}
	long long ll = l <= 0 ? l / d : (l - 1) / d + 1, rr = r >= 0 ? r / d : (r + 1) / d - 1;
	if(tl < ll)
		tl = ll;
	if(tr > rr)
		tr = rr;
}
int main()
{
	while(scanf("%d%d%d%d%d%d%d", &a, &b, &c, &x1, &x2, &y1, &y2) == 7) {
	if(a < 0) {
		a = -a;
		x1 = -x1;
		x2 = -x2;
		swap(x1, x2);
	}
	if(b < 0) {
		b = -b;
		y1 = -y1;
		y2 = -y2;
		swap(y1, y2);
	}
	if(!a && !b)
		printf("%lld\n", c ? 0 : (long long)max(x2 - x1 + 1, 0) * max(y2 - y1 + 1, 0));
	else if(!a)
		printf("%d\n", max(x2 - x1 + 1, 0) * (c % b == 0 && y1 <= -c / b && -c / b <= y2));
	else if(!b)
		printf("%d\n", (c % a == 0 && x1 <= -c / a && -c / a <= x2) * max(y2 - y1 + 1, 0));
	else
	{
		r = exgcd(a, b, x, y);
		if(c % r != 0)
			puts("0");
		else
		{
			tl = -INF;
			tr = INF;
			check(x1 - (long long)x * (-c / r), x2 - (long long)x * (-c / r), b / r);
			check(y1 - (long long)y * (-c / r), y2 - (long long)y * (-c / r), -a / r);
			printf("%lld\n", max(tr - tl + 1, 0LL));
		}
	}
	}
	return 0;
}
