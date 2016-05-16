#include <stdio.h>
int t, n, a, mx, i;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		mx = 0;
		scanf("%d", &n);
		for(i = 0; i < n; ++i)
		{
			scanf("%d", &a);
			if(mx < a)
				mx = a;
		}
		printf("%d\n", mx);
	}
	return 0;
}
