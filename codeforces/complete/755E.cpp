#include <stdio.h>
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	if(m < 2 || m > 3 || n < 4 + (m == 2))
		puts("-1");
	else
	{
		printf("%d\n", n - 1);
		for(int i = 2; i <= n; ++i)
			printf("%d %d\n", m == 2 || i <= 4 ? i - 1 : 3, i);
	}
	return 0;
}
