#include <cstdio>
const int maxn = 1010;
int t, n, now, ans;
char str[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		now = ans = 0;
		scanf("%d%s", &n, str);
		for(int i = 0; i <= n; ++i)
		{
			str[i] -= '0';
			if(!str[i])
				continue;
			if(now < i)
			{
				ans += i - now;
				now = i;
			}
			now += str[i];
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
