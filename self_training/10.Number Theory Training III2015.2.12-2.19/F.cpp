#include <cmath>
#include <cstdio>
int t, n, m, ans;
int phi(int x)
{
	int ret = x;
	for(int i = 2; i * i <= x; ++i)
		if(x % i == 0)
		{
			ret -= ret / i;
			while(x % i == 0)
				x /= i;
		}
	if(x > 1)
		ret -= ret / x;
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1, j = (int)sqrt(n); i <= j; ++i)
		{
			if(n % i != 0)
				continue;
			if(i >= m)
				ans += phi(n / i);
			if(i * i < n && n / i >= m)
				ans += phi(i);
		}
		printf("%d\n", ans);
	}
	return 0;
}
