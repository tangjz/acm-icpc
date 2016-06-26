#include <cstdio>
typedef long long LL;
int t, a, b, c, d;
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
bool check(int x, int a, int b)
{
	int s, t, r = exgcd(a, b, s, t);
	if(x % r)
		return 0;
	a /= r;
	b /= r;
	x /= r;
	LL xs = (LL)s * x, xt = (LL)t * x;
	if(xs < 0)
		return xt / a >= (-xs - 1) / b + 1;
	if(xt < 0)
		return xs / b >= (-xt - 1) / a + 1;
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &a, &b, &c, &d);
		puts(c % a == 0 && d % b == 0
		|| c % b == 0 && d % a == 0
		|| c % a == 0 && c % b == 0 && check(d, a, b)
		|| d % a == 0 && d % b == 0 && check(c, a, b) ? "YES" : "NO");
	}
	return 0;
}
