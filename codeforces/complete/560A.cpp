#include <stdio.h>
int n, x, ans;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		ans |= x == 1;
	}
	printf("%d\n", ans ? -1 : 1);
	return 0;
}
