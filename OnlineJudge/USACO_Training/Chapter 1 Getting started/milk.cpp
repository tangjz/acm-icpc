/*
ID: tangjin2
LANG: C++
TASK: milk
*/
#include <cstdio>
int n, m, milk[1001], ans;
int main()
{
	freopen("milk.in", "r", stdin);
	freopen("milk.out", "w", stdout);
	int x, y;
	scanf("%d%d", &n, &m);
	while(m--)
	{
		scanf("%d%d", &x, &y);
		milk[x] += y;
	}
	for(int i = 0; n; ++i)
		if(milk[i])
			if(n > milk[i])
			{
				ans += i * milk[i];
				n -= milk[i];
			}
			else
			{
				ans += i * n;
				n = 0;
			}
	printf("%d\n", ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
