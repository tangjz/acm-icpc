#include <cstdio>
int main()
{
	int m, n;
	while(scanf("%d%d", &m, &n) == 2)
		switch(m)
		{
			case 0 : printf("%d\n", n + 1); break;
			case 1 : printf("%d\n", n + 2); break;
			case 2 : printf("%d\n", n + n + 3); break;
			case 3 : printf("%d\n", (1 << n + 3) - 3);
		}
	return 0;
}
