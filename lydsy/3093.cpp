#include <cstdio>
int t, n, p, q;
int main()
{
	while(scanf("%d%d%d", &n, &p, &q) == 3)
		printf("Case %d: %.4f\n", ++t, (q + 1) / (p + 2.0));
	return 0;
}
