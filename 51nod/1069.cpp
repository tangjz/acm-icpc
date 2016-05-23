#include <stdio.h>
int n, sg, x;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		sg ^= x;
	}
	puts(sg ? "A" : "B");
}
