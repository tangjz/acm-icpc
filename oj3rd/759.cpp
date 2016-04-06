#include <cstdio>
int t, n, x;
long double ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", &x);
			ans += (long long)x * i * (n - i + 1);
		}
		ans /= (long long)n * (n + 1) >> 1;
		printf("%.3f\n", (double)ans);
	}
	return 0;
}
