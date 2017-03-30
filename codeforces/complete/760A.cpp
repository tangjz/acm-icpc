#include <stdio.h>
int m, d, days;
int main()
{
	scanf("%d%d", &m, &d);
	if(m <= 7 && (m & 1)
	|| m > 7 && !(m & 1))
		days = 31;
	else if(m != 2)
		days = 30;
	else
		days = 28;
	printf("%d\n", (days - (8 - d) - 1) / 7 + 2);
	return 0;
}
