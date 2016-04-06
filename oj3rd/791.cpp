#include <cstdio>
#include <cstring>
int n, a[101], x, k = 0;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		memset(a, 0, sizeof a);
		while(n--)
		{
			scanf("%d", &x);
			++a[x];
		}
		x = a[0];
		for(int i = 0; i <= 100; ++i)
			if(x < a[i])
				x = a[i];
		k ? putchar('\n') : k = 1;
		while(x--)
		{
			for(int i = 0; i <= 100; ++i)
				if(a[i] > x)
					printf("   *");
				else if(a[i])
					printf("    ");
			putchar('\n');
		}
		for(int i = 0; i <= 100; ++i)
			if(a[i])
				printf("%4d", i);
		putchar('\n');
	}
	return 0;
}
