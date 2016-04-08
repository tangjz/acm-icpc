#include <cstdio>
int n, ans;
int main()
{
	scanf("%d", &n);
	++n;
	ans = n;
	for(int i = 2; (long long)i * i <= n; ++i)
		if(n % i == 0)
		{
			ans -= ans / i;
			while(n % i == 0)
				n /= i;
		}
	if(n > 1)
		ans -= ans / n;
	printf("%d\n", ans);
	return 0;
}
