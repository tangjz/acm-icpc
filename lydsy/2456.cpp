/*
 * 因为这个众数出现次数超过一半，所以可以把任意两个不同的数相抵消，最后剩下的一定是众数
 */
#include <cstdio>
int n, x, ans, cnt;
char ch;
inline void getint(int &x)
{
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0';
}
int main()
{
	getint(n);
	while(n--)
	{
		getint(x);
		if(!cnt) ans = x;
		ans == x ? ++cnt : --cnt;
	}
	printf("%d\n", ans);
	return 0;
}
