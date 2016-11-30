#include <stdio.h>
const int maxn = 10000001;
int f[maxn];
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
inline void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	int n, x, y;
	while(scanf("%d", &n) == 1)
	{
		long long ans = 0;
		for(int i = 2; i <= n; ++i)
		{
			for(int j = i, k = 1; j <= n; j += i, ++k)
				if(exgcd(k, i, x, y) == 1)
				{
					if(x < 0)
						x += i;
					upd(f[j], k * x);
				}
			ans += f[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
