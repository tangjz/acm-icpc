#include <stdio.h>
int t, r1, x1, y1, r2, x2, y2;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d%d%d", &r1, &x1, &y1, &r2, &x2, &y2);
		puts(r1 >= r2 && (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 - r2) * (r1 - r2) ? "Rich" : "Dead");
	}
	return 0;
}
