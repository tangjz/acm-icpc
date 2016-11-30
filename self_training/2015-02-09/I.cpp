#include <cstdio>
int n, k;
long long ans;
int main()
{
	while(scanf("%d%d", &n, &k) == 2)
	{
		ans = (long long)n * k;
		if(n > k)
			n = k;
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = k / (k / i) <= n ? k / (k / i) : n;
			ans -= (long long)k / i * (i + j) * (j - i + 1) >> 1;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
