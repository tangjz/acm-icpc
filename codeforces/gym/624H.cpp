#include <cctype>
#include <cstdio>
template<class T> void scan(T& x)
{
	static int ch, flag;
	while(!isdigit(ch = getchar()) && ch != '-');
	x = (flag = ch == '-') ? 0 : ch - '0';
	while(isdigit(ch = getchar()))
		x = (x << 3) + (x << 1) + ch - '0';
	if(flag)
		x = -x;
}int t, n, x, y, ans;
int main()
{
	scan(t);
	while(t--)
	{
		ans = 0;
		scan(n);
		while(n--)
		{
			scan(x), scan(y);
			for(int i = 1; i <= 10; ++i)
				if(x * x + y * y <= 400 * i * i)
				{
					ans += 11 - i;
					break;
				}
		}
		printf("%d\n", ans);
	}
	return 0;
}
