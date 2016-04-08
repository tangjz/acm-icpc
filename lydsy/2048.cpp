#include <cmath>
#include <cstdio>
long long n, m;
double ans;
int main()
{
	scanf("%lld%lld", &n, &m);
	if(n <= 1e4)
		for(int i = 1; i <= n; ++i)
			ans += 0.5 / i;
	else
		ans = 0.5 * (log(n + 1) + 0.5772156649);
	ans *= m;
	printf("%d\n", (int)(ans - 1e-8));
	return 0;
}
