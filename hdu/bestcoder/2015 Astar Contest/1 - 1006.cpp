#include <cstdio>
int t, n;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		printf("Case #%d:\n%.6f %.6f\n", Case, 1 + (n - 2) * 19 / 27.0, (46 - 38.0 / n) / (19 - 11.0 / n));
	}
	return 0;
}
