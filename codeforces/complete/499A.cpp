#include <cstdio>
int n, x, lastr = 1, l, r, ans;
int main()
{
	scanf("%d%d", &n, &x);
	while(n--)
	{
		scanf("%d%d", &l, &r);
		ans += (l - lastr) % x + r - l + 1;
		lastr = r + 1;
	}
	printf("%d\n", ans);
	return 0;
}
