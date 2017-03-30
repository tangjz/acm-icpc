#include <cmath>
#include <stdio.h>
int t, p, n, k;
double ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d%d", &p, &n, &k);
		for(int i = 0; i <= k; ++i)
			ans += log((n - i) * p) - log((n - i) * p + 1);
		printf("%.9f\n", exp(ans));
	}
	return 0;
}
