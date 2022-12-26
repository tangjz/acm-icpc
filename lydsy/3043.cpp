/*
 * 差分序列，统计正数和和负数和
 * 最小值次操作后才有序列的值多种可能
 */
#include <cstdio>
int n, ch, last, now;
long long x, y;
void scan(int &t)
{
	while((ch = getchar()) < '0' || ch > '9');
	t = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		t = (t << 3) + (t << 1) + ch - '0';
}
inline void calc(int t) { t < 0 ? y -= t : x += t; }
int main()
{
	scan(n), scan(last);
	while(--n)
	{
		scan(now);
		calc(now - last);
		last = now;
	}
	if(x < y) { long long t = x; x = y; y = t; }
	printf("%lld\n%lld\n", x, x - y + 1);
	return 0;
}
