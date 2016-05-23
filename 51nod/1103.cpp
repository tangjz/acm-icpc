#include <stdio.h>
const int maxn = 50001;
int n, a[maxn], pos[maxn];
int main()
{
	pos[0] = 1;
	scanf("%d", &n);
	for(int i = 1, c = 0; i <= n; ++i)
	{
		scanf("%d", a + i);
		c = (c + a[i]) % n;
		if(!pos[c])
			pos[c] = i + 1;
		else
		{
			printf("%d\n", i - pos[c] + 1);
			for(int j = pos[c]; j <= i; ++j)
				printf("%d\n", a[j]);
			return 0;
		}
	}
	puts("No Solution");
	return 0;
}
