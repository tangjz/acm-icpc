#include <cstdio>
int n, ans[111111];
int main()
{
	for(int i = 1; i <= 100000; ++i)
	{
		int j = i, k = i;
		while(j)
		{
			k += j % 10;
			j /= 10;
		}
		if(!ans[k])
			ans[k] = i;
	}
	while(scanf("%d", &n) == 1)
		printf("%d\n", ans[n]);
	return 0;
}
