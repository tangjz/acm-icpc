#include <stdio.h>
int n, x, min = 1001, ans;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		ans += x;
		if((x & 1) && min > x)
			min = x;
	}
	if(ans & 1)
		ans -= min;
	if(!ans)
		puts("NIESTETY");
	else
		printf("%d\n", ans);
	return 0;
}
