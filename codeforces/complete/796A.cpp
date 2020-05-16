#include <stdio.h>
#include <algorithm>
int n, m, q, x, ans;
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	ans = ~0u >> 1;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &x);
		if(!x)
			continue;
		if(x <= q && std::abs(i - m) < ans)
			ans = std::abs(i - m);
	}
	printf("%d\n", ans * 10);
	return 0;
}
