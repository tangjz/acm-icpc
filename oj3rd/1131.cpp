#include <cstdio>
#include <cstring>
int n, m, a[2000001], x;
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(a, 0, sizeof a);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", &x);
			if(!a[x])
				a[x] = i;
		}
		for(int i = 0; i < m; ++i)
		{
			scanf("%d", &x);
			if(!a[x])
				puts("error");
			else
				printf("%d\n", a[x]);
		}
	}
	return 0;
}
