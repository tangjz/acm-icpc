#include <stdio.h>
const int maxn = 1501;
long double f[maxn], x;
int main()
{
	f[1] = x = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(~i & 1)
			x = x * (i - 1) / i;
		f[i] = f[i - 1] + x;
	}
	int t, n;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		printf("Case %d: %.6f\n", Case, (double)f[n] + 1e-10);
	}
	return 0;
}
