#include <cstdio>
const int maxn = 10001;
int n, a[maxn], sum, ans;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		sum = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			sum += a[i];
		}
		if(sum % n != 0)
		{
			puts("-1");
			continue;
		}
		ans = 1;
		for(int i = 1; i <= n; ++i)
			if(sum / n <= a[i])
				break;
			else
				ans += sum / n - a[i];
		printf("%d\n", ans);
	}
	return 0;
}
