#include <stdio.h>
int n, pre, cur = -1;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		pre = cur;
		scanf("%d", &cur);
	}
	puts(pre == -1 ? cur != 15 && cur != 0 ? "-1" : cur == 0 ? "UP" : "DOWN" : (pre < cur) != (cur == 15 || cur == 0) ? "UP" : "DOWN");
	return 0;
}
