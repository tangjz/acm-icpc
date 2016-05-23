#include <stdio.h>
int t, n;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		puts(n % 7 != 0 && n % 7 != 2 ? "A" : "B");
	}
	return 0;
}
