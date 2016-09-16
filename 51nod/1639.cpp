#include <cstdio>

int main()
{
	int n;
	double ans = 1;
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
		ans = ans * (i << 1) / (i << 1 | 1);
	printf("%f\n", ans);
	return 0;
}
